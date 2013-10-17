//Elsa Gonsiorowski
//October 7, 2011
//Rensselaer Polytechnic Institute

//This file contains the ross functions for the model: init/final, foward/reverse event, mapping, and support

#include <stdio.h>
#include <assert.h>

#include "ross.h"
#include "run_config.h"
#include "gates_model.h"
#include "library_types.h"

//exten'd variables
unsigned int source_interval = 1;
unsigned int sink_interval = 5;

char global_input[LP_COUNT+1][LINE_LENGTH + 1];
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

void SWAP(unsigned int *a, unsigned int *b) {
    // a ^= b; b ^= a; a ^= b; 
    unsigned int temp = *a;
    *a = *b;
    *b = temp;
    global_swap_count++;
}

void gates_init(gate_state *s, tw_lp *lp){
    unsigned int self = lp->gid;
    unsigned int gate = lp->id % TOTAL_GATE_COUNT;
    int i;
    s->received_events = 0;
    s->roll_backs = 0;
    s->calc = FALSE;
    s->wave_print = FALSE;
    
    assert(self < COPY_COUNT * TOTAL_GATE_COUNT);

    //FUCK THIS NOISE
    if (self == 0) {
        for (i = 0; i < g_tw_nlp; i++) {
            int stride = NP_PER_INSTANCE;
            int line_gid = -1;
            int c = sscanf(global_input[i], "%d", &line_gid);
            assert(line_gid == (i*stride));
        }
    }

    
    int gid = -1;
    int type = -1;
    unsigned int inputs[16][2];
    
    int count = sscanf(global_input[gate], "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &gid, &type, &inputs[0][0], &inputs[0][1],  &inputs[1][0], &inputs[1][1], &inputs[2][0], &inputs[2][1], &inputs[3][0], &inputs[3][1], &inputs[4][0], &inputs[4][1],  &inputs[5][0], &inputs[5][1], &inputs[6][0], &inputs[6][1], &inputs[7][0], &inputs[7][1], &inputs[8][0], &inputs[8][1],  &inputs[9][0], &inputs[9][1], &inputs[10][0], &inputs[10][1], &inputs[11][0], &inputs[11][1], &inputs[12][0], &inputs[12][1],  &inputs[13][0], &inputs[13][1], &inputs[14][0], &inputs[14][1], &inputs[15][0], &inputs[15][1]);

    if (count < 2) {
        printf("Error on %d from reading: \"%s\"\n", self, global_input[gate]);
        error_count++;
    }
    // assert(count >= 2);
    assert(gid == self);

    s->gate_type = type;
    
    /*
    if (s->gate_type == INPUT_GATE) {
        if (count > 3) {
            printf("This input gate %u has more than one input %d !\n", self, count -2);
        } else if (count == 3) {
            if (inputs[0] >= TOTAL_GATE_COUNT) {
                if (instance_x != 0) { //This goes to a different instance
                    //needs to link to instance at (intsance_x - 1, instance_y)
                    int real_id = TOTAL_GATE_COUNT - inputs[0];
                    inputs[0] = (instance_0 - TOTAL_GATE_COUNT) + real_id;
                    s->gate_type = DFF_GATE;
                } else {
                    count--;
                }
            }
        } 
    }
    */
    
    // because of integer division, fanout case not handled
    int input_count = (count - 2) / 2;

    // synthetic circuit mappings
    if (instance_x(self) == 0) {
        int tmp = 0;
        unsigned int in2[16][2];
        for (i = 0; i < input_count; i++) {
            if (inputs[i][0] < TOTAL_GATE_COUNT) {
                in2[tmp][0] = inputs[i][0];
                in2[tmp][1] = inputs[i][1];
                tmp++;
            }
        }
        input_count = tmp;
        for (i = 0; i < tmp; i++) {
            inputs[i][0] = in2[i][0] + instance_0(self);
            inputs[i][1] = in2[i][1];
        }
    } else {
        for (i = 0; i < input_count; i++) {
            if (inputs[i][0] >= TOTAL_GATE_COUNT) {
                int gate_id = inputs[i][0] - TOTAL_GATE_COUNT;
                inputs[i][0] = (instance_0(self) - TOTAL_GATE_COUNT) + gate_id;
            } else {
                inputs[i][0] = inputs[i][0] + instance_0(self);
            }
        }
    }
    
    for (i = 0; i < input_count; i ++) {
        assert(inputs[i][0] >= 0);
        assert(inputs[i][0] < COPY_COUNT * TOTAL_GATE_COUNT);
    }
    
    int input_size = gate_input_size[type];
    assert(input_count <= input_size);
    s->inputs = tw_calloc(TW_LOC, "gates_init_gate_input", sizeof(vector) + ((input_count) * sizeof(pair)), 1);
    s->inputs->alloc = input_count;
    s->inputs->size = input_count;
    
    for (i = 0; i < input_count; i++) {
        s->inputs->array[i].gid = inputs[i][0];
        s->inputs->array[i].value = inputs[i][1];
    }
    
    // Set up internal vector
    int internal_size = gate_internal_size[type];
    s->internals = tw_calloc(TW_LOC, "gates_init_gate_internal", sizeof(vector) + internal_size * sizeof(pair), 1);
    s->internals->alloc = internal_size;
    s->internals->size = 0;

    // Set up output vector
    int output_size = gate_output_size[type];

    // special cases
    if (type == fanout_TYPE) {
        output_size = inputs[1][0];
    }
    
    // if (COPY_COUNT > 1) {
    //     output_size++;
    // }
    
    s->outputs = tw_calloc(TW_LOC, "gates_init_gate_output", sizeof(vector) + output_size * sizeof(pair), 1);
    s->outputs->alloc = output_size;
    s->outputs->size = 0;
    
    if (s->gate_type == output_gate_TYPE) {
        //s->outputs->array[0].gid = SINK_ID;
        //s->outputs->size++;
    }
    
    //Setup messages have a staggered arrival btwn 1 and 8
    tw_event *e = tw_event_new(self, 1 + tw_rand_unif(lp->rng)*3, lp);
    message *msg = tw_event_data(e);
    msg->type = SETUP_MSG;
    msg->data.gid = self;
    msg->data.value = self;
    tw_event_send(e);
    
    if (s->gate_type == input_gate_TYPE) {
        tw_event *e2 = tw_event_new(self, 10.5, lp);
        message *msg2 = tw_event_data(e2);
        msg2->type = SOURCE_MSG;
        msg2->data.gid = self;
        msg2->data.value = -1;
        tw_event_send(e2);
    }
    
    /* if (s->gate_type == CLOCK_GATE) { */
    /*     tw_event *e2 = tw_event_new(self, 10.5, lp); */
    /*     message *msg2 = tw_event_data(e2); */
    /*     msg2->type = CLOCK_MSG; */
    /*     msg2->data.gid = self; */
    /*     msg2->data.value = 0; */
    /*     tw_event_send(e2); */
    /* } */
    
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
    
    if (in_msg->type == SETUP_MSG) {
        if (in_msg->data.gid == self) {
            for (i = 0; i < s->inputs->size; i++) {
                double jitter = (tw_rand_unif(lp->rng)*3);
                double window_start = 6 - tw_now(lp);
                tw_event *e = tw_event_new(s->inputs->array[i].gid, window_start + jitter, lp);
                message *msg = tw_event_data(e);
                msg->type = SETUP_MSG;
                msg->data.gid = self;
                msg->data.value = s->inputs->array[i].value;
                tw_event_send(e);
            }

            if (self == 0) {
                // LP 0 is specially designated to inform of wave printing (gid array filled on node 0)
                for (i = 0; i < WAVE_COUNT; i++) {
                    double jitter = (tw_rand_unif(lp->rng)*2);
                    double window_start = 4 - tw_now(lp);
                    tw_event *w = tw_event_new(wave_gids[i], window_start + jitter, lp);
                    message *wm = tw_event_data(w);
                    wm->type = WAVE_MSG;
                    // wave id (ascii value)
                    wm->data.gid = 33 + i;
                    wm->data.value = TRUE;
                    tw_event_send(w);
                }
            }
        } else {
            if (s->outputs->alloc <= s->outputs->size) {
                printf("Node %u wants to add %u to outputs, but alloc is %d and size is %d:: ", self, in_msg->data.value, s->outputs->alloc, s->outputs->size);
                for (i = 0; i < s->outputs->size; i++) {
                    printf("%u ", s->outputs->array[i].gid);
                }
                printf("::\n");
                assert(s->outputs->alloc > s->outputs->size);
            }
            assert(in_msg->data.value >= 0);
            assert(in_msg->data.value < s->outputs->alloc);
            assert(in_msg->data.gid >= 0);
            assert(in_msg->data.gid < COPY_COUNT * TOTAL_GATE_COUNT);

            // special case
            if(s->gate_type == fanout_TYPE) {
                in_msg->data.value = s->outputs->size;
            }

            SWAP(&(s->outputs->array[in_msg->data.value].gid), &(in_msg->data.gid));
            s->outputs->size++;
            // !! NOTE: s->outputs is non-contiguously filled !!
            // (except for fanout case)
        }
    } else if (in_msg->type == SOURCE_MSG) {
        //s->gate_function(s->inputs, s->outputs);
        //printf("Source doing a wave of inputs\n");
        //Assume node 0 is an input
        if (self == 0) {
            tw_output(lp, "Source nodes doing a wave of inputs at %f.\n", tw_now(lp));
            // printf("Source nodes doing a wave of inputs at %f.\n", tw_now(lp));
        }
        for (i = 0; i < s->outputs->size; i++) {
            double delay = g_tw_lookahead;
            unsigned int recipient = s->outputs->array[i].gid;
            if (recipient >= FANOUT_START) {
                delay = 0.2;
            } else {
                double jitter = (tw_rand_unif(lp->rng)) * (1.0 - (2.0 * MESSAGE_PAD));
                delay = MESSAGE_PAD + jitter;
            }
            tw_event *e = tw_event_new(recipient, delay, lp);
            message *msg = tw_event_data(e);
            msg->type = LOGIC_CARY_MSG;
            msg->data.gid = self;
            msg->data.value = (tw_rand_unif(lp->rng) < 0.5) ? 0 : 1;
            tw_event_send(e);
        }
        
        tw_event *e = tw_event_new(self, source_interval, lp);
        message *msg = tw_event_data(e);
        msg->type = SOURCE_MSG;
        msg->data.gid = self;
        msg->data.value = -1;
        tw_event_send(e);
    } else if (in_msg->type == CLOCK_MSG) {
        for (i = 0; i < s->outputs->size; i++) {
            double jitter = (tw_rand_unif(lp->rng)) * (1.0 - (2.0 * MESSAGE_PAD));
            tw_event *e = tw_event_new(s->outputs->array[i].gid, MESSAGE_PAD + jitter, lp);
            message *msg = tw_event_data(e);
            msg->type = LOGIC_CARY_MSG;
            msg->data.gid = self;
            msg->data.value = in_msg->data.value;
            tw_event_send(e);
        }
        
        tw_event *c = tw_event_new(self, 1, lp);
        message *cmsg = tw_event_data(c);
        cmsg->type = CLOCK_MSG;
        cmsg->data.gid = self;
        cmsg->data.value = LOGIC_NOT(in_msg->data.value);
        tw_event_send(c);
        
    } else if (in_msg->type == LOGIC_CARY_MSG) {
        if (s->gate_type == fanout_TYPE) {
            assert(s->inputs->size == 1);
            assert(s->inputs->array[0].gid == in_msg->data.gid);
            SWAP(&(s->inputs->array[0].value), &(in_msg->data.value));
            for (i = 0; i < s->outputs->size; i++) {
                double jitter = (tw_rand_unif(lp->rng)) * (1.0 - (2.0 * MESSAGE_PAD));
                tw_event *e = tw_event_new(s->outputs->array[i].gid, 0.2 + jitter, lp);
                message *msg = tw_event_data(e);
                msg->type = LOGIC_CARY_MSG;
                msg->data.gid = self;
                msg->data.value = s->inputs->array[0].value;
                tw_event_send(e);
            }
        } else {
            assert(s->outputs->size <= s->outputs->alloc);
            for (i = 0; i < s->inputs->size; i++) {
                if(s->inputs->array[i].gid == in_msg->data.gid){
                    SWAP(&(s->inputs->array[i].value), &(in_msg->data.value));
                    break;
                }
            }
            
            //If i have received any logic in, i need to recalculate & send my outputs
            if (s->calc == FALSE) {
                bf->c0 = 1;
                s->calc = TRUE;
                double jitter_offset = clock_round(tw_now(lp));
                if (MESSAGE_PAD + jitter_offset < 0 ) printf("ERROR: %u is sending a message at a bad time: %f\n", self, MESSAGE_PAD + jitter_offset);
                tw_event *e = tw_event_new(self, jitter_offset + 0.5, lp);
                message *msg =  tw_event_data(e);
                msg->type = LOGIC_CALC_MSG;
                msg->data.gid = self;
                tw_event_send(e);
            }
        }
    } else if (in_msg->type == LOGIC_CALC_MSG) {
        int changed = function_array[s->gate_type](s->inputs, s->internals, s->outputs);
        s->calc = FALSE;
        
        //send event to outputs
        for(i = 0; i < s->outputs->size; i++){
            double delay = g_tw_lookahead;
            unsigned int recipient = s->outputs->array[i].gid;
            if (recipient >= FANOUT_START) {
                delay = 0.2;
            } else {
                double jitter = (tw_rand_unif(lp->rng)) * (1.0 - (2.0 * MESSAGE_PAD));
                delay = MESSAGE_PAD + jitter;
            }
            tw_event *e = tw_event_new(recipient, delay, lp);
            message *msg = tw_event_data(e);
            msg->type = LOGIC_CARY_MSG;
            msg->data.gid = self;
            msg->data.value = s->outputs->array[i].value;
            tw_event_send(e);

            //printf("SEND\tgid: %u\tgtype: %d\tsend: %u\tto: %u\n", self, s->gate_type, s->outputs->array[i].value, s->outputs->array[i].gid);
        }
        if (s->wave_print && changed) {
            // assume OUTPUT_gate type
            wave_print(tw_now(lp), s->inputs->array[0].value, s->wave_id);
        }
    } else if (in_msg->type == WAVE_MSG) {
        // turn on wave printing for this LP
        SWAP(&(s->wave_print), &(in_msg->data.value));
        s->wave_id = (char) in_msg->data.gid;
    } else {
        printf("ERROR: could not process message type %d on lp %u\n", in_msg->type, self);
    }
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
        if (in_msg->data.gid == self) {
            assert(s->inputs->size >= 0);
            for (i = 0; i < s->inputs->size; i++) {
                tw_rand_reverse_unif(lp->rng);
            }

            if (self == 0) {
                for (i = 0; i < WAVE_COUNT; i++) {
                    tw_rand_reverse_unif(lp->rng);
                }
            }

        } else {
            assert(s->outputs->size > 0);
            SWAP(&(s->outputs->array[in_msg->data.value].gid), &(in_msg->data.gid));
            s->outputs->size--;
        }
    } else if (in_msg->type == SOURCE_MSG) {
        assert(s->outputs->size >= 0);
        for (i = 0; i < s->outputs->size; i++) {
            if (s->outputs->array[i].gid < FANOUT_START) {
                tw_rand_reverse_unif(lp->rng);
            }
            tw_rand_reverse_unif(lp->rng);
        }
    } else if (in_msg->type == CLOCK_MSG) {
        for (i = 0; i < s->outputs->size; i++) {
            tw_rand_reverse_unif(lp->rng);
        }
    } else if (in_msg->type == LOGIC_CARY_MSG) {
        if (s->gate_type == fanout_TYPE) {
            SWAP(&(s->inputs->array[0].value), &(in_msg->data.value));
            for (i = 0; i < s->outputs->size; i++) {
                tw_rand_reverse_unif(lp->rng);
            }
        } else {
            assert(s->inputs->size >= 0);
            for (i = 0; i < s->inputs->size; i++) {
                if(s->inputs->array[i].gid == in_msg->data.gid){
                    SWAP(&(s->inputs->array[i].value), &(in_msg->data.value));
                    break;
                }
            }
            
            //If I took the calc=FALSE path, bf->c0 == 1
            if (bf->c0 == 1) {
                s->calc = FALSE;
            }
        }
    } else if (in_msg->type == LOGIC_CALC_MSG) {
        s->calc = TRUE;
        assert(s->outputs->size >= 0);
        for(i = 0; i < s->outputs->size; i++){
            if (s->outputs->array[i].gid < FANOUT_START) {
                tw_rand_reverse_unif(lp->rng);
            }
        }
    } else if (in_msg->type == WAVE_MSG) {
        if (self != 0){
            SWAP(&(s->wave_print), &(in_msg->data.value));
        }
    } else {
        printf("ERROR: could not process reverse message type %d on lp %u\n", in_msg->type, self);
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
    assert(gid < COPY_COUNT * TOTAL_GATE_COUNT);
    if (NP_PER_INSTANCE > 0) {
        return (tw_peid) (NP_PER_INSTANCE * instance_id(gid)) + instance_node(gid);
    }
    return node_instance(gid);
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

tw_lp * gates_custom_round_robin_mapping_to_local(tw_lpid gid){
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
        (event_f) gates_event,
        (revent_f) gates_event_rc,
        (final_f) gates_final,
        (map_f) gates_custom_round_robin_mapping_to_pe,
        sizeof(gate_state)  },
    { 0 },
};

