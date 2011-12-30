//Elsa Gonsiorowski
//October 7, 2011
//Rensselaer Polytechnic Institute

#include <stdio.h>
#include "ross.h"
#include "gate.h"

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

char global_input[LP_COUNT][LINE_LENGTH + 1];

void gates_init(gate_state *s, tw_lp *lp){
    int self = lp->gid;
    s->received_events = 0;
    
    if (self == SOURCE_ID) {
        s->gate_type = SOURCE_GATE;
        s->outputs = tw_calloc(TW_LOC, "gates_init_source_lp", sizeof(vector) + SOURCE_OUTPUTS * sizeof(pair), 1);
        
        //event to start simulation
        tw_event *e = tw_event_new(self, 10, lp);
        message *msg = tw_event_data(e);
        msg->type = SOURCE_MSG;
        tw_event_send(e);
    } else if (self == SINK_ID) {
        s->gate_type = SINK_GATE;
    } else if(self < TOTAL_GATE_COUNT + 2){
        int type = -1;
        int output_count = 0;
        int inputs[MAX_GATE_INPUTS];
        
        int count = sscanf(global_input[lp->id], "%d %d %d %d %d %d", &output_count, &type, &inputs[0], &inputs[1], &inputs[2], &inputs[3]);
        
        s->gate_type = type;
        if (s->gate_type == INPUT_GATE) {
            inputs[0] = SOURCE_ID;
            count++;
        }
        
        s->inputs = tw_calloc(TW_LOC, "gates_init_gate_input", sizeof(vector) + (count - 2) * sizeof(pair), 1);
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
        
        printf("%d is all done! my type is %d\n", self, s->gate_type);
    } else {
        printf("%d is an unused lp\n", self);
    }
    
}

void gates_event(gate_state *s, tw_bf *bf, message *in_msg, tw_lp *lp){
    int i;
    int self = lp->gid;
    //printf("Processing event type %d on lp %d\n", in_msg->type, self);
    s->received_events++;
    
    if (in_msg->type == SETUP_MSG) {
        if (in_msg->data.gid == self) {
            for (i = 0; i < s->inputs->size; i++) {
                tw_event *e = tw_event_new(s->inputs->array[i].gid, 1, lp);
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
        int i;
        for (i = 0; i < s->outputs->size; i++) {
            tw_event *e = tw_event_new(s->outputs->array[i].gid, 1, lp);
            message *msg = tw_event_data(e);
            msg->type = LOGIC_CARY_MSG;
            msg->data.gid = lp->gid;
            msg->data.value = i%2;
            tw_event_send(e);
        }
        
        tw_event *e = tw_event_new(SOURCE_ID, 1, lp);
        message *msg = tw_event_data(e);
        msg->type = SOURCE_MSG;
        tw_event_send(e);
    } else if (self == SINK_ID) {
        //s->gate_func(s->inputs, s->outputs);
        //printf("SUNK\tgid: %d\tval: %d\n", (int) in_msg->data.gid, (int) in_msg->data.value);
    } else if (in_msg->type == LOGIC_CARY_MSG) {
        for (i = 0; i < s->inputs->size; i++) {
            if(s->inputs->array[i].gid == in_msg->data.gid){
                s->inputs->array[i].value = in_msg->data.value;
                //printf("RECV\tgid: %d\tval: %d\tor?: %d\tfrom: %d\n",lp->gid, s->inputs->array[i].value, msg->data.value, s->inputs->array[i].gid);
                break;
            }
        }
        
        //If i have received any logic in, i need to recalculate & send my outputs
        tw_event *e = tw_event_new(self, 0.5, lp);
        message *msg =  tw_event_data(e);
        msg->type = LOGIC_CALC_MSG;
        tw_event_send(e);
    } else if (in_msg->type == LOGIC_CALC_MSG) {
        function_array[s->gate_type](s->inputs, s->outputs);
        
        //send event to outputs
        for(i = 0; i < s->outputs->size; i++){
            tw_event *e = tw_event_new(s->outputs->array[i].gid, 0.5, lp);
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
    return (tw_peid)gid / g_tw_nlp;
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

tw_peid olsr_map(tw_lpid gid){
    return (tw_peid)gid / g_tw_nlp;
}

const tw_optdef gates_opts[] = {
    TWOPT_GROUP("Gates Model"),
    TWOPT_END(),
};

#define gates_main main

int gates_main(int argc, char* argv[]){
    int i;
    
    tw_opt_add(gates_opts);
    
    tw_init(&argc, &argv);
    tw_define_lps(LP_COUNT, sizeof(message), 0);
    
    for (i = 0; i < g_tw_nlp; i++) {
        tw_lp_settype(i, &gates_lps[0]);
    }
    
    //IO
    //printf("%d is attempting to start io\n", g_tw_mynode);
    MPI_File fh;
    MPI_Request req;
    
    //char filename[100] = "/Users/elsagonsiorowski/Desktop/MY_ROSS/testfile.txt";
    char filename[100] = "/home/gonsie/ccx_mpi.bench";
    MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
    
    //NOTE: for some reason count is off
    int start = 0;
    if (g_tw_mynode == 0) start = 2;
    int offset = ((g_tw_mynode * LP_COUNT) - 2) * (LINE_LENGTH-1);
    printf("offset is %d\n", offset);
    for (i = start; i < LP_COUNT && g_tw_mynode * LP_COUNT + i < TOTAL_GATE_COUNT + 2; i++) {
        MPI_File_iread_at(fh, offset + (i*LINE_LENGTH) - i, global_input[i], LINE_LENGTH-1, MPI_CHAR, &req);
        //if (g_tw_mynode == 3) printf("<%d read line %s>", g_tw_mynode, global_input[i]);
    }
    MPI_File_close(&fh);
    
    
    tw_run();
    
    tw_end();
    
    return 0;
}
