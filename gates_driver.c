//Elsa Gonsiorowski
//October 7, 2011
//Rensselaer Polytechnic Institute

//This file contains the ross functions for the model: init/final, foward/reverse event, mapping, and support

#include <stdio.h>
#include <assert.h>

#include "ross.h"
#include "run_config.h"
#include "gates_model.h"
#include "gate.h"

unsigned int source_interval = 1;
unsigned int sink_interval = 5;

char global_input[LP_COUNT+1][LINE_LENGTH + 1];

//#define DEBUG_TRACE 1
#if DEBUG_TRACE
FILE * node_out_file;
#endif

int global_swap_count = 0;
int error_count = 0;

inline void SWAP(int *a, int *b) {
    // a ^= b; b ^= a; a ^= b; 
    int temp = *a;
    *a = *b;
    *b = temp;
    global_swap_count++;
}

void gates_init(gate_state *s, tw_lp *lp){
    int self = lp->gid;
    s->received_events = 0;
    s->calc = FALSE;
    
    if (self < TOTAL_GATE_COUNT) {
        int type = -1;
        int output_count = 0;
        int inputs[MAX_GATE_INPUTS];
        
        int count = sscanf(global_input[lp->id], "%d %d %d %d %d %d", &output_count, &type, &inputs[0], &inputs[1], &inputs[2], &inputs[3]);
        if (count < 2) {
            error_count++;
            if (error_count < 10) printf("count is %d lp %d (locally %d) has line %s\n", count, self, (int) lp->id, global_input[lp->id]);
            return;
        }
        s->gate_type = type;
        if (s->gate_type == INPUT_GATE) {
	  //inputs[0] = SOURCE_ID;
	  //count++;
        }
        
        s->inputs = tw_calloc(TW_LOC, "gates_init_gate_input", sizeof(vector) + ((count - 2) * sizeof(pair)), 1);
        s->inputs->size = count - 2;
        
        switch (s->inputs->size) {
            case 4:
                s->inputs->array[3].gid = inputs[3];
            case 3:
                s->inputs->array[2].gid = inputs[2];
            case 2:
                s->inputs->array[1].gid = inputs[1];
            case 1:
                s->inputs->array[0].gid = inputs[0];
            default:
                break;
        }
        
        s->outputs = tw_calloc(TW_LOC, "gates_init_gate_output", sizeof(vector) + output_count * sizeof(pair), 1);
        s->outputs->size = 0;
        
        if (s->gate_type == OUTPUT_GATE) {
	  //s->outputs->array[0].gid = SINK_ID;
	  //s->outputs->size++;
        }
        
        tw_event *e = tw_event_new(self, 1, lp);
        message *msg = tw_event_data(e);
        msg->type = SETUP_MSG;
        msg->data.gid = self;
        msg->data.value = self;
        tw_event_send(e);
        
        if (s->gate_type == INPUT_GATE) {
            tw_event *e2 = tw_event_new(self, 10.5, lp);
            message *msg2 = tw_event_data(e2);
            msg2->type = SOURCE_MSG;
            msg2->data.gid = self;
	    msg2->data.value = -1;
            tw_event_send(e2);
        }
        
        //printf("%d is all done! my type is %d\n", self, s->gate_type);
    } else {
        //printf("ERROR: lp with gid %d (>= %d) was inited \n", self, TOTAL_GATE_COUNT);
    }
    
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



void gates_event(gate_state *s, tw_bf *bf, message *in_msg, tw_lp *lp){
    int i;
    int self = lp->gid;
    
    *(int *) bf = (int) 0;
    
#if DEBUG_TRACE
    fprintf(node_out_file, "FWDE: #%d %lu %lu %lu %lu %d %2.3f %d %d\n", self, lp->rng->Cg[0], lp->rng->Cg[1], lp->rng->Cg[2], lp->rng->Cg[3], in_msg->type, tw_now(lp), in_msg->data.gid, global_swap_count);
    fflush(node_out_file);
#endif
    
    //printf("Processing event type %d on lp %d\n", in_msg->type, self);
    /*
     if (tw_now(lp) >= 29.2) {
     printf("#%d processing event type %d\n", self, in_msg->type);
     }
     */
    
    s->received_events++;
    if(lp->id == 0 && error_count != 0){
        tw_error(TW_LOC, "ERROR: %d errors detected in init on node %d\n", error_count, (int) g_tw_mynode);
    }
    
    if (in_msg->type == SETUP_MSG) {
        if (in_msg->data.gid == self) {
            for (i = 0; i < s->inputs->size; i++) {
                double jitter = (tw_rand_unif(lp->rng)) * (1.0 - (2.0 * MESSAGE_PAD));
                tw_event *e = tw_event_new(s->inputs->array[i].gid, MESSAGE_PAD + jitter, lp);
                message *msg = tw_event_data(e);
                msg->type = SETUP_MSG;
                msg->data.gid = self;
                msg->data.value = self;
                tw_event_send(e);
            }
        } else {
            SWAP(&(s->outputs->array[s->outputs->size].gid), &(in_msg->data.value));
            s->outputs->size++;
        }
    } else if (in_msg->type == SOURCE_MSG) {
        //s->gate_function(s->inputs, s->outputs);
        //printf("Source doing a wave of inputs\n");
        for (i = 0; i < s->outputs->size; i++) {
            double jitter = (tw_rand_unif(lp->rng)) * (1.0 - (2.0 * MESSAGE_PAD));
            tw_event *e = tw_event_new(s->outputs->array[i].gid, MESSAGE_PAD + jitter, lp);
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
    } else if (self == SINK_ID) {
        //s->gate_func(s->inputs, s->outputs);
        //printf("SUNK\tgid: %d\tval: %d\n", (int) in_msg->data.gid, (int) in_msg->data.value);
        if (in_msg->type == SINK_MSG) {
            printf("%2.3f: Sink has processed %d messages\n", tw_now(lp), s->received_events);
            tw_event *e = tw_event_new(self, sink_interval, lp);
            message *msg = tw_event_data(e);
            msg->type = SINK_MSG;
            msg->data.gid = self;
            msg->data.value = -1;
            tw_event_send(e);
        }
    } else if (in_msg->type == LOGIC_CARY_MSG) {
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
            if (MESSAGE_PAD + jitter_offset < 0 ) printf("ERROR: %d is sending a message at a bad time: %f\n", self, MESSAGE_PAD + jitter_offset);
            tw_event *e = tw_event_new(self, jitter_offset + 0.5, lp);
            message *msg =  tw_event_data(e);
            msg->type = LOGIC_CALC_MSG;
            msg->data.gid = self;
            tw_event_send(e);
        }
    } else if (in_msg->type == LOGIC_CALC_MSG) {
        s->stat_output_change += function_array[s->gate_type](s->inputs, s->outputs);
        s->calc = FALSE;
        //send event to outputs
        for(i = 0; i < s->outputs->size; i++){
            double jitter = (tw_rand_unif(lp->rng)) * (1.0 - (2.0 * MESSAGE_PAD));
            tw_event *e = tw_event_new(s->outputs->array[i].gid, MESSAGE_PAD + jitter, lp);
            message *msg = tw_event_data(e);
            msg->type = LOGIC_CARY_MSG;
            msg->data.gid = self;
            msg->data.value = s->outputs->array[i].value;
            tw_event_send(e);
            //printf("SEND\tgid: %d\tgtype: %d\tsend: %d\tto: %d\n", self, s->gate_type, s->outputs->array[i].value, s->outputs->array[i].gid);
        }
    } else {
        printf("ERROR: could not process message type %d on lp %d\n", in_msg->type, self);
    }
}

void gates_event_rc(gate_state *s, tw_bf *bf, message *in_msg, tw_lp *lp){
    int i;
    int self = lp->gid;
    
    s->received_events--;
    //printf("%d reversing %d\n", self, in_msg->type);
    //fflush(stdout);
    assert(in_msg->type >= 0);
    assert(self >= 0);
    assert(in_msg->data.gid >= 0);
    if (in_msg->type == SETUP_MSG) {
        if (in_msg->data.gid == self) {
            assert(s->inputs->size >=0);
            for (i = 0; i < s->inputs->size; i++) {
                tw_rand_reverse_unif(lp->rng);
            }
        } else {
            assert(s->outputs->size > 0);
            s->outputs->size--;
            SWAP(&(s->outputs->array[s->outputs->size].gid), &(in_msg->data.value));
        }
    } else if (in_msg->type == SOURCE_MSG) {
        assert(s->outputs->size >= 0);
        for (i = 0; i < s->outputs->size; i++) {
            tw_rand_reverse_unif(lp->rng);
            tw_rand_reverse_unif(lp->rng);
        }
    } else if (self == SINK_ID) {
        //do nothing
    } else if (in_msg->type == LOGIC_CARY_MSG) {
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
    } else if (in_msg->type == LOGIC_CALC_MSG) {
        s->calc = TRUE;
        assert(s->outputs->size >= 0);
        for(i = 0; i < s->outputs->size; i++){
            tw_rand_reverse_unif(lp->rng);
        }
    } else {
        printf("ERROR: could not process reverse message type %d on lp %d\n", in_msg->type, self);
    }
    
#if DEBUG_TRACE
    fprintf(node_out_file, "REVE: #%d %lu %lu %lu %lu %d %2.3f %d %d\n", self, lp->rng->Cg[0], lp->rng->Cg[1], lp->rng->Cg[2], lp->rng->Cg[3], in_msg->type, tw_now(lp), in_msg->data.gid, global_swap_count);
    fflush(node_out_file);
#endif
    
}

void gates_final(gate_state *s, tw_lp *lp){
    int self = lp->gid;
    
    //wrap up
    if (self == SOURCE_ID || self == SINK_ID) {
        printf("%d processed %d events\n", self, s->received_events);
    }
    
    if(FALSE) {
        printf("#%d e%d\n", self, s->received_events);
        fflush(stdout);
    }
    return;
}

//#define VERIFY_MAPPING 1

tw_peid gates_custom_round_robin_mapping_to_pe(tw_lpid gid){
    return (tw_peid) gid % NP_COUNT;
}

void gates_custom_round_robin_mapping_setup(void){
    tw_pe *pe;
    int kpid;
    int nlp_per_kp;
    int lpgid, lplid;
    int i, j;
    
    //Minimum lps per kp, and how many kps have 1 extra lp
    int lps_per_kp = g_tw_nlp / g_tw_nkp;
    int extra_kps = g_tw_nlp - (lps_per_kp * g_tw_nkp);
    
    //The gid of my g_tw_lp[0]
    g_tw_lp_offset = g_tw_mynode;
    
#if VERIFY_MAPPING
    printf("Node %d: nlp %d, offset %d, lps_per_kp %d, extra_kps %d\n", (int) g_tw_mynode, (int) g_tw_nlp, (int) g_tw_lp_offset, lps_per_kp, extra_kps);
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
	    
            for (j = 0; j < nlps; j++, lpgid += NP_COUNT, lplid++) {
                assert(lpgid < TOTAL_GATE_COUNT);
                
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
    assert(gid >= 0);
    assert(gid < LP_COUNT * tw_nnodes() + EXTRA_LP_COUNT);
    
    int id = gid / NP_COUNT;
    return g_tw_lp[id];
}


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
                    printf("Node %d\tPE %d\tKP %d\t%d\n", g_tw_mynode, pe->id, kpid, (int )lpid + g_tw_lp_offset);
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

tw_lptype gates_lps[] = {
    {   (init_f) gates_init,
        (event_f) gates_event,
        (revent_f) gates_event_rc,
        (final_f) gates_final,
        (map_f) gates_custom_round_robin_mapping_to_pe,
        sizeof(gate_state)  },
    { 0 },
};

