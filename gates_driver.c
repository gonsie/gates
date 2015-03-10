//Elsa Gonsiorowski
//October 7, 2011
//Rensselaer Polytechnic Institute

//This file contains the ross functions for the model: init/final, foward/reverse event, mapping, and support

#include <stdio.h>
#include <assert.h>

#include "ross.h"
#include "run_config.h"
#include "gates_model.h"
#include "library.h"
#include "chaco_partition.h"

//exten'd variables
unsigned int source_interval = 1;
unsigned int sink_interval = 5;

char global_input[MAX_LP_COUNT+1][LINE_LENGTH + 1];
int wave_gids[WAVE_COUNT];

// #define DEBUG_TRACE 1
#if DEBUG_TRACE
FILE * node_out_file;
#endif

// each PE has its own unique file pointer
FILE * wave_out_file;
double latest_ts = 0.0;

int global_swap_count = 0;
int error_count = 0;

void SWAP(int *a, int *b) {
    // a ^= b; b ^= a; a ^= b;
    int temp = *a;
    *a = *b;
    *b = temp;
    global_swap_count++;
}

void gates_init(gate_state *s, tw_lp *lp){
    unsigned int self = lp->gid;
    unsigned int gate = lp->id;
    int i;
    s->received_events = 0;
    s->roll_backs = 0;
    s->wave_print = FALSE;

    assert(self < TOTAL_GATE_COUNT);

    int gid, type;
    int offset;

    char* line = global_input[gate];
    int count = sscanf(line, "%d %d %n", &gid, &type, &offset);
    line += offset;

    if (count != 2) {
        printf("Error on %d from reading: \"%s\"\n", self, global_input[gate]);
        error_count++;
    }

    assert(gid == self);

    s->gate_type = type;

    // Init inputs
    s->inputs = tw_calloc(TW_LOC, "gates_init_gate_input", gate_input_size[s->gate_type] * sizeof(int), 1);
    for (i = 0; i < gate_input_size[s->gate_type]; i++) {
        int from_gid;
        assert(1 == sscanf(line, "%d%n", &from_gid, &offset));
        line += offset;
        if (from_gid >= 0) {
            s->inputs[i] = from_gid;
        }
    }

    // Init internals
    s->internals = tw_calloc(TW_LOC, "gates_init_gate_internal", gate_internal_size[s->gate_type] * sizeof(int), 1);

    // Init outputs
    if (type == fanout_TYPE) {
        // HACK fanouts store output size in s->internals
        assert(1 == sscanf(line, "%d%n", &s->internals, &offset));
        line += offset;
        s->internals = 0;
        // set to 0 to count up. Essetially this value doesn't need to be read since it doesn't go anywhere
    }
    s->output_gid = tw_calloc(TW_LOC, "gates_init_gate_output", gate_output_size[s->gate_type] * sizeof(int), 1);
    s->output_pin = tw_calloc(TW_LOC, "gates_init_gate_output", gate_output_size[s->gate_type] * sizeof(int), 1);
    s->output_val = tw_calloc(TW_LOC, "gates_init_gate_output", gate_output_size[s->gate_type] * sizeof(int), 1);
    if (type != fanout_TYPE) {
        for (i = 0; i < gate_output_size[s->gate_type]; i++) {
            int to_gid, to_pin;
            int c = sscanf(line, "%d %d%n", &to_gid, &to_pin, &offset);
            if (c != 2) {
                if (type == input_gate_TYPE) {
                    break;
                }
                printf("ERROR: Gate %d type %d Expected %d inputs and %d output-pairs on line %s\n", self, type, gate_input_size[type], gate_output_size[type], global_input[gate]);
                assert(c == 2);
            }
            line += offset;
            if (to_gid >= 0) {
                s->output_gid[i] = to_gid;
                s->output_pin[i] = to_pin;
            }
        }
    }

    //Setup messages have a staggered arrival btwn 1 and 8
    tw_event *e = tw_event_new(self, 1 + tw_rand_unif(lp->rng)*3, lp);
    message *msg = tw_event_data(e);
    msg->type = INIT_MSG;
    msg->id = -1;
    msg->value = -1;
    tw_event_send(e);

    if (s->gate_type == input_gate_TYPE) {
        tw_event *e2 = tw_event_new(self, 10.5, lp);
        message *msg2 = tw_event_data(e2);
        msg2->type = SOURCE_MSG;
        msg2->id = self;
        msg2->value = -1;
        tw_event_send(e2);
    }

    //printf("%u is all done! my type is %d\n", self, s->gate_type);

}

tw_stime clock_round(tw_stime now){
    int floor_now = now;
    double diff = now - ((double) floor_now);
    if (diff > 0.5) {
        return 1.0 - diff;
    } else {
        return -1.0 * diff;
    }
}

void wave_print(double timestamp, int value, char id) {
    if (timestamp > latest_ts) {
        fprintf(wave_out_file, "#%f\n", timestamp);
        latest_ts = timestamp;
    }
    fprintf(wave_out_file, "%d%c\n", value, id);
}

void gates_event(gate_state *s, tw_bf *bf, message *in_msg, tw_lp *lp){
    int i;
    unsigned int self = lp->gid;
    long start_count = lp->rng->count;

    *(int *) bf = (int) 0;

#if DEBUG_TRACE
    fprintf(node_out_file, "FWDE: #%u %lu %lu %lu %lu %d %2.3f %u %d\n", self, lp->rng->Cg[0], lp->rng->Cg[1], lp->rng->Cg[2], lp->rng->Cg[3], in_msg->type, tw_now(lp), in_msg->data.gid, global_swap_count);
    fflush(node_out_file);
#endif

    //printf("Processing event type %d on lp %u\n", in_msg->type, self);
    /*
     if (tw_now(lp) >= 29.2) {
     printf("#%u processing event type %d\n", self, in_msg->type);
     }
     */

    s->received_events++;
    if(lp->id == 0 && error_count != 0){
        tw_error(TW_LOC, "ERROR: %d errors detected in init on node %d\n", error_count, g_tw_mynode);
    }
    assert(error_count == 0);

    if (in_msg->type == INIT_MSG) {
        // send messages along input pins, to init fanouts
        // send my gid and pin to receive on
        for (i = 0; i < gate_input_size[s->gate_type]; i++) {
            double jitter = (tw_rand_unif(lp->rng)*3);
            double window_start = 6 - tw_now(lp);
            assert (window_start + jitter >= 0.1);
            tw_event *e = tw_event_new(s->inputs[i], window_start + jitter, lp);
            message *msg = tw_event_data(e);
            msg->type = SETUP_MSG;
            msg->id = self;
            msg->value = i;
            tw_event_send(e);
        }

        if (self == 0) {
            // LP 0 is specially designated to inform of wave printing (wave_gid array filled on node 0)
            for (i = 0; i < WAVE_COUNT; i++) {
                double jitter = (tw_rand_unif(lp->rng)*2);
                double window_start = 4 - tw_now(lp);
                assert (window_start + jitter >= 0.1);
                tw_event *w = tw_event_new(wave_gids[i], window_start + jitter, lp);
                message *wm = tw_event_data(w);
                wm->type = WAVE_MSG;
                // wave id (ascii value)
                wm->id = 33 + i;
                wm->value = TRUE;
                tw_event_send(w);
            }
        }
    } else if (in_msg->type == SETUP_MSG) {
        // regular gates ignore setup messages
        if (s->gate_type == fanout_TYPE) {
            SWAP(&(s->output_gid[(int)s->internals]), &(in_msg->id));
            SWAP(&(s->output_pin[(int)s->internals]), &(in_msg->value));
            s->internals++;
        }
    } else if (in_msg->type == SOURCE_MSG) {
        //Assume node 0 is an input //TODO: Can't assume this with patitioning
        if (self == 0) {
            tw_output(lp, "Source nodes doing a wave of inputs at %f.\n", tw_now(lp));
            // printf("Source nodes doing a wave of inputs at %f.\n", tw_now(lp));
        }
        for (i = 0; i < gate_output_size[s->gate_type]; i++) {
            double delay = g_tw_lookahead;
            double jitter = (tw_rand_unif(lp->rng)) * (1.0 - (2.0 * MESSAGE_PAD));
            delay = MESSAGE_PAD + jitter;
            assert(delay >= 0.1);
            tw_event *e = tw_event_new(s->output_gid[i], delay, lp);
            message *msg = tw_event_data(e);
            msg->type = LOGIC_MSG;
            msg->id = s->output_pin[i];
            msg->value = (tw_rand_unif(lp->rng) < 0.5) ? 0 : 1;
            tw_event_send(e);
        }

        tw_event *e = tw_event_new(self, source_interval, lp);
        message *msg = tw_event_data(e);
        msg->type = SOURCE_MSG;
        msg->id = self;
        msg->value = -1;
        tw_event_send(e);
    } else if (in_msg->type == LOGIC_MSG) {
        int in_pin = in_msg->id;
        if (s->inputs[in_pin] == in_msg->value) {
            // No state change. event chain dies here
            goto unified_exit;
        }
        BOOL rising = (s->inputs[in_pin] < in_msg->value);
        SWAP(&(s->inputs[in_pin]), &(in_msg->value));

        // store current internal pin state
        if (gate_internal_size[s->gate_type] > 0) {
            assert(gate_internal_size[s->gate_type] == 2 && "ERROR: internal size != 2");
            in_msg->internal_pin0 = s->internals[0];
            in_msg->internal_pin1 = s->internals[1];
        }

        int changed = function_array[s->gate_type](s->inputs, s->internals, s->output_val);
        if (!changed) {
            // No output change. event chain dies here
            goto unified_exit;
        }
        for (i = 0; i < gate_output_size[s->gate_type]; i++){
            float delay = delay_array[s->gate_type](in_pin, i, rising);
            assert(delay >= 0.01);
            tw_event *e = tw_event_new(s->output_gid[i], delay, lp);
            message *msg = tw_event_data(e);
            msg->type = LOGIC_MSG;
            msg->id = s->output_pin[i];
            msg->value = s->output_val[i];
            tw_event_send(e);
        }

        if (s->wave_print && changed) {
            // assume OUTPUT_gate type
            wave_print(tw_now(lp), s->inputs[0], s->wave_id);
        }
    } else if (in_msg->type == WAVE_MSG) {
        // turn on wave printing for this LP
        SWAP(&(s->wave_print), &(in_msg->value));
        s->wave_id = (char) in_msg->id;
    } else {
        printf("ERROR: could not process message type %d on lp %u\n", in_msg->type, self);
    }
unified_exit:
    in_msg->rng_count = lp->rng->count - start_count;
}

void gates_event_rc(gate_state *s, tw_bf *bf, message *in_msg, tw_lp *lp){
    int i;
    unsigned int self = lp->gid;

    s->received_events--;
    s->roll_backs++;
    //printf("%u reversing %d\n", self, in_msg->type);
    //fflush(stdout);
    assert(in_msg->type >= 0);
    if (in_msg->type == SETUP_MSG) {
        if (s->gate_type == fanout_TYPE) {
            s->internals--;
            SWAP(&(s->output_gid[(int)s->internals]), &(in_msg->id));
            SWAP(&(s->output_pin[(int)s->internals]), &(in_msg->value));
        }
    } else if (in_msg->type == LOGIC_MSG) {
        if (s->inputs[in_msg->id] == in_msg->value){
            return;
        }
        SWAP(&(s->inputs[in_msg->id]), &(in_msg->value));

        // store current internal pin state
        if (gate_internal_size[s->gate_type] > 0) {
            assert(gate_internal_size[s->gate_type] == 2 && "ERROR: internal size != 2");
            s->internals[0] = in_msg->internal_pin0;
            s->internals[1] = in_msg->internal_pin1;
        }

    } else if (in_msg->type == WAVE_MSG) {
        if (self != 0){
            SWAP(&(s->wave_print), &(in_msg->value));
        }
    } else {
        printf("ERROR: could not process reverse message type %d on lp %u\n", in_msg->type, self);
    }

    long count = in_msg->rng_count;
    while (count--) {
        tw_rand_reverse_unif(lp->rng);
    }

#if DEBUG_TRACE
    fprintf(node_out_file, "REVE: #%u %lu %lu %lu %lu %d %2.3f %u %d\n", self, lp->rng->Cg[0], lp->rng->Cg[1], lp->rng->Cg[2], lp->rng->Cg[3], in_msg->type, tw_now(lp), in_msg->data.gid, global_swap_count);
    fflush(node_out_file);
#endif

}

void gates_final(gate_state *s, tw_lp *lp){
    unsigned int self = lp->gid;

    if (g_tw_synchronization_protocol == 3) {
        printf("LP %d had %d rollbacks.\n", self, s->roll_backs);
    }

    if(FALSE) {
        printf("#%u e%d\n", self, s->received_events);
        fflush(stdout);
    }
    return;
}

//#define VERIFY_MAPPING 1

tw_peid gates_custom_round_robin_mapping_to_pe(tw_lpid gid){
    assert(gid >= 0);
    assert(gid < TOTAL_GATE_COUNT);
    return (tw_peid) gid % GLOBAL_NP_COUNT;
}

void gates_custom_round_robin_mapping_setup(void){
    tw_pe *pe;
    int kpid;
    int lpgid, lplid;
    int j;

    //Minimum lps per kp, and how many kps have 1 extra lp
    int lps_per_kp = g_tw_nlp / g_tw_nkp;
    int extra_kps = g_tw_nlp - (lps_per_kp * g_tw_nkp);

    //The gid of my g_tw_lp[0], round robin stride
    int stride;
    g_tw_lp_offset = ((g_tw_mynode / GLOBAL_NP_COUNT) * TOTAL_GATE_COUNT) + (g_tw_mynode % GLOBAL_NP_COUNT);
    stride = GLOBAL_NP_COUNT;

#if VERIFY_MAPPING
    printf("Node %d: nlp %d, offset %d, lps_per_kp %d, extra_kps %d\n", g_tw_mynode, g_tw_nlp, g_tw_lp_offset, lps_per_kp, extra_kps);
#endif

    //This loop happens once on each pe
    //set starting local and global ids for the LPs on this node
    for (lplid = 0, lpgid = g_tw_lp_offset, pe = NULL; (pe = tw_pe_next(pe)); ) {

        //For each kp
        for (kpid = 0; kpid < g_tw_nkp; kpid++) {

            tw_kp_onpe(kpid, pe);

            //lps on this particular kp
            int nlps = lps_per_kp;
            if (kpid < extra_kps) {
                nlps++;
            }

            for (j = 0; j < nlps; j++, lpgid += stride, lplid++) {
                tw_lp_onpe(lplid, pe, lpgid);
                tw_lp_onkp(g_tw_lp[lplid], g_tw_kp[kpid]);

#if VERIFY_MAPPING
                if (0 == j) {
                    printf("PE %d\tKP %d\tLP %d\n", pe->id, kpid, lpgid);
                }
#endif
            }
        }
    }
}

tw_lp * gates_custom_round_robin_mapping_to_local(tw_lpid gid){
    int id = 0;
    int ins_gid = gid % TOTAL_GATE_COUNT;
    id = ins_gid / GLOBAL_NP_COUNT;
    assert(id < LP_COUNT + 1);
    assert(id >= 0);

    return g_tw_lp[id];
}
/*
tw_peid gates_custom_many_copies_round_robin_mapping_to_pe(tw_lpid gid){
    assert(gid >= 0);
    assert(gid < COPY_COUNT * TOTAL_GATE_COUNT);
    if (NP_PER_INSTANCE > 0) {
        return (tw_peid) (NP_PER_INSTANCE * instance_id(gid)) + instance_node(gid);
    }
    return node_instance(gid);
}

void gates_custom_many_copies_round_robin_mapping_setup(void){
    tw_pe *pe;
    int kpid;
    int lpgid, lplid;
    int j;

    //Minimum lps per kp, and how many kps have 1 extra lp
    int lps_per_kp = g_tw_nlp / g_tw_nkp;
    int extra_kps = g_tw_nlp - (lps_per_kp * g_tw_nkp);

    //The gid of my g_tw_lp[0], round robin stride
    int stride;
    if (NP_PER_INSTANCE > 0) {
        g_tw_lp_offset = ((g_tw_mynode / NP_PER_INSTANCE) * TOTAL_GATE_COUNT) + (g_tw_mynode % NP_PER_INSTANCE);
        stride = NP_PER_INSTANCE;
    } else {
        g_tw_lp_offset = g_tw_mynode * INSTANCE_PER_NP * TOTAL_GATE_COUNT;
        stride = 1;
    }

#if VERIFY_MAPPING
    printf("Node %d: nlp %d, offset %d, lps_per_kp %d, extra_kps %d\n", g_tw_mynode, g_tw_nlp, g_tw_lp_offset, lps_per_kp, extra_kps);
#endif

    //This loop happens once on each pe
    //set starting local and global ids for the LPs on this node
    for (lplid = 0, lpgid = g_tw_lp_offset, pe = NULL; (pe = tw_pe_next(pe)); ) {

        //For each kp
        for (kpid = 0; kpid < g_tw_nkp; kpid++) {

            tw_kp_onpe(kpid, pe);

            //lps on this particular kp
            int nlps = lps_per_kp;
            if (kpid < extra_kps) {
                nlps++;
            }

            for (j = 0; j < nlps; j++, lpgid += stride, lplid++) {
                tw_lp_onpe(lplid, pe, lpgid);
                tw_lp_onkp(g_tw_lp[lplid], g_tw_kp[kpid]);

#if VERIFY_MAPPING
                if (0 == j) {
                    printf("PE %d\tKP %d\tLP %d\n", pe->id, kpid, lpgid);
                }
#endif
            }
        }
    }
}

tw_lp * gates_custom_many_copies_round_robin_mapping_to_local(tw_lpid gid){
    int id = 0;
    if (NP_PER_INSTANCE > 0) {
        int ins_gid = gid % TOTAL_GATE_COUNT;
        id = ins_gid / NP_PER_INSTANCE;
        assert(id < LP_COUNT + 1);
    } else {
        id = gid - (node_instance(gid) * INSTANCE_PER_NP * TOTAL_GATE_COUNT);
        assert(id < INSTANCE_PER_NP * TOTAL_GATE_COUNT);
    }
    assert(id >= 0);

    return g_tw_lp[id];
}

int instance_id(unsigned int gid) {
    return gid / TOTAL_GATE_COUNT;
}

int instance_node(unsigned int gid) {
    if (NP_PER_INSTANCE > 0) {
        // round robin mapping among processors
        return  (gid % TOTAL_GATE_COUNT) % NP_PER_INSTANCE;
    }
    return 0;
}

int node_instance(unsigned int gid) {
    if (INSTANCE_PER_NP > 0) {
        return instance_id(gid) / INSTANCE_PER_NP;
    }
    return 0;
}

int instance_x(unsigned int gid) {
    return instance_id(gid) % X_COUNT;
}

int instance_y(unsigned int gid) {
    return instance_id(gid) / X_COUNT;
}

int instance_0(unsigned int gid) {
    return instance_id(gid) * TOTAL_GATE_COUNT;
}
*/
/*
tw_peid gates_custom_linear_mapping_to_pe(tw_lpid gid){
    if (gid >= EXTRA_LP_COUNT * (LP_COUNT + 1)) {
        return (tw_peid) ((gid - EXTRA_LP_COUNT) / LP_COUNT);
    } else {
        return (tw_peid) gid / (LP_COUNT + 1);
    }
}

void gates_custom_linear_mapping_setup(void){
    tw_pe *pe;
    int nlp_per_kp;
    int lpid, kpid;
    int i, j;

    nlp_per_kp = ceil((double) g_tw_nlp / (double) g_tw_nkp);
    if(!nlp_per_kp) tw_error(TW_LOC, "Not enough KPs defined: %d", g_tw_nkp);

    g_tw_lp_offset = (g_tw_mynode * LP_COUNT) + min(g_tw_mynode, EXTRA_LP_COUNT);

#if VERIFY_MAPPING
    printf("Node %d: nlp %lld, offset %lld\n", g_tw_mynode, g_tw_nlp, g_tw_lp_offset);
#endif

    for (kpid = 0, lpid = 0, pe = NULL; (pe = tw_pe_next(pe)); ) {

        for (i = 0; i < nkp_per_pe; i++, kpid++) {
            tw_kp_onpe(kpid, pe);

            for (j = 0; j < nlp_per_kp && lpid < g_tw_nlp; j++, lpid++) {
                tw_lp_onpe(lpid, pe, g_tw_lp_offset + lpid);
                tw_lp_onkp(g_tw_lp[lpid], g_tw_kp[kpid]);
#if VERIFY_MAPPING
                if (0 == j % 20000) {
                    printf("Node %d\tPE %d\tKP %d\t%d\n", g_tw_mynode, pe->id, kpid, lpid + g_tw_lp_offset);
                }
#endif
            }
        }
    }

    if (!g_tw_lp[g_tw_nlp - 1]) {
        tw_error(TW_LOC, "Not all LPs defined! (g_tw_nlp=%d)", g_tw_nlp);
    }

    if (g_tw_lp[g_tw_nlp - 1]->gid != g_tw_lp_offset + g_tw_nlp - 1) {
        tw_error(TW_LOC, "LPs not sequentially enumerated!");
    }
}

tw_lp * gates_custom_linear_mapping_to_local(tw_lpid lpid){
    assert(lpid >= 0);
    assert(lpid < LP_COUNT * tw_nnodes() + EXTRA_LP_COUNT);

    int id = lpid - g_tw_lp_offset;

    return g_tw_lp[id];
}
*/

tw_lptype gates_lps[] = {
    {   (init_f) gates_init,
        (pre_run_f) NULL,
        (event_f) gates_event,
        (revent_f) gates_event_rc,
        (final_f) gates_final,
        (map_f) gates_custom_round_robin_mapping_to_pe,
        sizeof(gate_state)  },
    { 0 },
};

