//Elsa Gonsiorowski
//October 7, 2011
//Rensselaer Polytechnic Institute

#include <stdio.h>
#include <libgen.h>
#include <assert.h>

#include "ross.h"
#include "gate.h"
#include "run_config.h"

gate_func function_array[GATE_TYPE_COUNT] = {
    &SOURCE_func,
    &SINK_func,
    &INPUT_func,
    &OUTPUT_func,
    &NOT_func,
    &DFF_func,
    &AND_func,
    &NAND_func,
    &OR_func,
    &NOR_func,
    &XOR_func,
    &XNOR_func,
};

char global_input[LP_COUNT+1][LINE_LENGTH + 1];
unsigned int source_interval = 1;
unsigned int sink_interval = 5;

int error_count = 0;

void gates_init(gate_state *s, tw_lp *lp){
    int self = lp->gid;
    s->received_events = 0;
    s->calc = FALSE;
    
    if (self == SOURCE_ID) {
        s->gate_type = SOURCE_GATE;
        s->outputs = tw_calloc(TW_LOC, "gates_init_source_lp", sizeof(vector) + SOURCE_OUTPUTS * sizeof(pair), 1);
        
        //event to start simulation
        tw_event *e = tw_event_new(self, 10.5, lp);
        message *msg = tw_event_data(e);
        msg->type = SOURCE_MSG;
        msg->data.gid = self;
        tw_event_send(e);
        
        printf("Source has completed init.\n");
    } else if (self == SINK_ID) {
        s->gate_type = SINK_GATE;
        tw_event *e = tw_event_new(self, 10 + sink_interval, lp);
        message *msg = tw_event_data(e);
        msg->type = SINK_MSG;
        msg->data.gid = self;
        tw_event_send(e);
    } else if(self < TOTAL_GATE_COUNT + 2){
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
            inputs[0] = SOURCE_ID;
            count++;
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
            s->outputs->array[0].gid = SINK_ID;
            s->outputs->size++;
        }
        
        tw_event *e = tw_event_new(self, 1, lp);
        message *msg = tw_event_data(e);
        msg->type = SETUP_MSG;
        msg->data.gid = self;
        tw_event_send(e);
        
        //printf("%d is all done! my type is %d\n", self, s->gate_type);
    } else {
        //printf("%d is an unused lp\n", self);
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
    //printf("Processing event type %d on lp %d\n", in_msg->type, self);
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
                tw_event_send(e);
            }
        } else {
            s->outputs->array[s->outputs->size].gid = in_msg->data.gid;
            s->outputs->size++;
        }
    } else if (in_msg->type == SOURCE_MSG && lp->gid == SOURCE_ID) {
        //s->gate_function(s->inputs, s->outputs);
        printf("Source doing a wave of inputs\n");
        int i;
        for (i = 0; i < s->outputs->size; i++) {
            double jitter = (tw_rand_unif(lp->rng)) * (1.0 - (2.0 * MESSAGE_PAD));
            tw_event *e = tw_event_new(s->outputs->array[i].gid, MESSAGE_PAD + jitter, lp);
            message *msg = tw_event_data(e);
            msg->type = LOGIC_CARY_MSG;
            msg->data.gid = lp->gid;
            msg->data.value = i%2;
            tw_event_send(e);
        }
        
        tw_event *e = tw_event_new(SOURCE_ID, source_interval, lp);
        message *msg = tw_event_data(e);
        msg->type = SOURCE_MSG;
        tw_event_send(e);
    } else if (lp->gid == SINK_ID) {
        //s->gate_func(s->inputs, s->outputs);
        //printf("SUNK\tgid: %d\tval: %d\n", (int) in_msg->data.gid, (int) in_msg->data.value);
        if (in_msg->type == SINK_MSG) {
            printf("Sink has processed %d messages\n", s->received_events);
            tw_event *e = tw_event_new(self, sink_interval, lp);
            message *msg = tw_event_data(e);
            msg->type = SINK_MSG;
            msg->data.gid = self;
            tw_event_send(e);
        }
    } else if (in_msg->type == LOGIC_CARY_MSG) {
        for (i = 0; i < s->inputs->size; i++) {
            if(s->inputs->array[i].gid == in_msg->data.gid){
                s->inputs->array[i].value = in_msg->data.value;
                //printf("RECV\tgid: %d\tval: %d\tor?: %d\tfrom: %d\n",lp->gid, s->inputs->array[i].value, msg->data.value, s->inputs->array[i].gid);
                break;
            }
        }
        
        //If i have received any logic in, i need to recalculate & send my outputs
        if (s->calc == FALSE) {
            s->calc = TRUE;
            double jitter_offset = clock_round(tw_now(lp));
            tw_event *e = tw_event_new(self, jitter_offset + MESSAGE_PAD, lp);
            message *msg =  tw_event_data(e);
            msg->type = LOGIC_CALC_MSG;
            tw_event_send(e);
        }
    } else if (in_msg->type == LOGIC_CALC_MSG) {
        function_array[s->gate_type](s->inputs, s->outputs);
        s->calc = FALSE;
        //send event to outputs
        for(i = 0; i < s->outputs->size; i++){
            double jitter = (tw_rand_unif(lp->rng)) * (1.0 - (2.0 * MESSAGE_PAD));
            tw_event *e = tw_event_new(s->outputs->array[i].gid, MESSAGE_PAD + jitter, lp);
            message *msg = tw_event_data(e);
            msg->type = LOGIC_CARY_MSG;
            msg->data.gid = lp->gid;
            msg->data.value = s->outputs->array[i].value;
            tw_event_send(e);
            //printf("SEND\tgid: %d\tgtype: %d\tsend: %d\tto: %d\n", lp->gid, s->gate_type, s->outputs->array[i].value, s->outputs->array[i].gid);
        }
    } else {
        printf("ERROR: could not process message type %d on lp %d\n", in_msg->type, self);
    }
}

void gates_final(gate_state *s, tw_lp *lp){
    //wrap up
    if (lp->gid == SOURCE_ID || lp->gid == SINK_ID) {
        printf("%d processed %d events\n", (int) lp->gid, s->received_events);
    }
    return;
}

tw_peid gates_map(tw_lpid gid){
    if (gid >= EXTRA_LP_COUNT * (LP_COUNT + 1)) {
        return (tw_peid) ((gid - EXTRA_LP_COUNT) / LP_COUNT);
    } else {
        return (tw_peid) gid / (LP_COUNT + 1);
    }
}

extern unsigned int nkp_per_pe;
#define VERIFY_MAPPING 1
void gates_custom_mapping(void){
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
    
    for (kpid = 0, lpid = 0, pe = NULL; pe = tw_pe_next(pe); ) {
        
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

tw_lp * gates_mapping_to_lp(tw_lpid lpid){
    assert(lpid >= 0);
    assert(lpid < LP_COUNT * tw_nnodes() + EXTRA_LP_COUNT);
    
    int id = lpid - g_tw_lp_offset;
    
    return g_tw_lp[id];
}

tw_lptype gates_lps[] = {
    {   (init_f) gates_init,
        (event_f) gates_event,
        (revent_f) NULL,
        (final_f) gates_final,
        (map_f) gates_map,
        sizeof(gate_state)  },
    { 0 },
};

const tw_optdef gates_opts[] = {
    TWOPT_GROUP("Gates Model"),
    TWOPT_UINT("source_interval", source_interval,"time between source sending waves of input"),
    TWOPT_UINT("sink_interval", sink_interval, "time between reporting of sink statistics"),
    TWOPT_END(),
};

#define gates_main main

int gates_main(int argc, char* argv[]){
    int i;
    
    tw_opt_add(gates_opts);
    
    tw_init(&argc, &argv);
    
    g_tw_mapping = CUSTOM;
    g_tw_custom_initial_mapping = &gates_custom_mapping;
    g_tw_custom_lp_global_to_local_map = &gates_mapping_to_lp;
    
    g_tw_events_per_pe = LP_COUNT * MAX_GATE_INPUTS + SOURCE_OUTPUTS * 2 + 32000;
    g_tw_lookahead = 0.09;
    
    g_tw_nlp = LP_COUNT;
    if (g_tw_mynode < EXTRA_LP_COUNT) {
        g_tw_nlp++;
    }
    
    tw_define_lps(g_tw_nlp, sizeof(message), 0);
    for (i = 0; i < g_tw_nlp; i++) {
        tw_lp_settype(i, &gates_lps[0]);
    }
    
    char filename[100] = "/ccx_mpi.bench";
    char *fullpath = dirname(argv[0]);
    strcat(fullpath, filename);
    if (g_tw_synchronization_protocol == 1) {
        //sequential
        FILE *my_file = fopen(fullpath, "r");
        for (i = 2; i < LP_COUNT; i++) {
            fgets(global_input[i], LINE_LENGTH, my_file);
        }
        fclose(my_file);
    } else {
        //IO
        //printf("%d is attempting to start io\n", g_tw_mynode);
        MPI_File fh;
        MPI_Status req;
        
        MPI_File_open(MPI_COMM_WORLD, fullpath, MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
        
        //NOTE: for some reason count is off
        int line_start, line_end;
        int current_id;
        if (g_tw_mynode == 0) {
            line_start = 0;
            line_end = g_tw_nlp - 2;
            current_id = 2;
        } else {
            line_start = (g_tw_mynode * LP_COUNT) + min(g_tw_mynode, EXTRA_LP_COUNT) - 2;
            line_end = line_start + g_tw_nlp;
            current_id = 0;
        }
        if (line_end > TOTAL_GATE_COUNT) {
            printf("ERROR: %d wants to read extra lines\n", g_tw_mynode);
            line_end = TOTAL_GATE_COUNT;
        }
//        printf("node %d starting at line %d and ending at line %d\n", (int) g_tw_mynode, line_start, line_end);
        for (i = line_start; i < line_end; i++, current_id++) {
            MPI_File_read_at(fh, i * (LINE_LENGTH - 1), global_input[current_id], LINE_LENGTH-1, MPI_CHAR, &req);
        }
        MPI_File_close(&fh);
    }
    
    tw_run();
    
    tw_end();
    
    return 0;
}
