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
    
    if(self < TOTAL_GATE_COUNT){
        int type = -1;
        int inputs[MAX_GATE_INPUTS];
        printf("%d (%d) scanning %s", (int) lp->id, self, global_input[lp->id]);
        int count = sscanf(global_input[lp->id], "%d %d %d %d %d", type, &inputs[0], &inputs[1], &inputs[2], &inputs[3]);
        
        s->gate_type = type;
        s->inputs->size = count - 1;
        
        if (s->gate_type == INPUT_GATE) {
            s->inputs->size = 1;
            inputs[0] = SOURCE_ID;
        }
        
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
    } else if (self == SOURCE_ID) {
        s->gate_type = SOURCE_GATE;
    } else if (self == SINK_ID) {
        s->gate_type = SINK_GATE;
    } else {
        //printf("%d is an unused lp\n", self);
    }
    
}

void gates_init_event_read(gate_state *s, tw_lp *lp){
    s->received_events = 0;
    
    int self = lp->gid;
    
    if (self == SOURCE_ID) {
        s->gate_type = SOURCE_GATE;
        s->outputs = tw_calloc(TW_LOC, "gates_init_source_lp", sizeof(struct vector) + SOURCE_OUTPUTS * sizeof(pair), 1);
        
        //event to open file and distribute gate info
        tw_event *e = tw_event_new(self, 1, lp);
        message *msg_e = tw_event_data(e);
        msg_e->type = READ_MSG;
        tw_event_send(e);
        
        //event to start simulation
        tw_event *f = tw_event_new(self, 10, lp);
        message *msg_f = tw_event_data(f);
        msg_f->type = SOURCE_MSG;
        tw_event_send(f);
    } else if (self == SINK_ID) {
        s->gate_type = SINK_ID;
    } else if (self < TOTAL_GATE_COUNT + 2) {
        s->inputs = tw_calloc(TW_LOC, "gates_init_gate_lp_input", sizeof(struct vector) + MAX_GATE_INPUTS * sizeof(pair), 1);
        s->outputs = tw_calloc(TW_LOC, "gates_init_gate_lp_output", sizeof(struct vector) + MAX_GATE_OUTPUTS * sizeof(pair), 1);
    } else {
        //printf("%d is an unused lp\n", self);
    }
}


void gates_event(gate_state *s, tw_bf *bf, message *in_msg, tw_lp *lp){
    int i;
    int self = lp->gid;
    //printf("Processing event type %d on lp %d\n", msg->type, (int) lp->gid);
    s->received_events++;
    
    if (in_msg->type == READ_MSG) {
        if (self == SOURCE_ID) {
            char buf[LINE_LENGTH];
            FILE *my_file = fopen("/Users/gonsie/Desktop/testfile.txt", "r");
            for (i = 0; i < TOTAL_GATE_COUNT; i++) {
                fgets(buf, LINE_LENGTH, my_file);
                
                //partitioning system
                int dest = i+2;
                
                tw_event *e = tw_event_new(dest, 1, lp);
                message *msg = tw_event_data(e);
                msg->type = READ_MSG;
                strcpy(msg->data.line, buf);
                tw_event_send(e);
            }
            fclose(my_file);
        } else {
            //printf("%d received the line %s", self, msg->data.line);
            
            char type[7];
            int inputs[MAX_GATE_INPUTS];
            int count = sscanf(in_msg->data.line, "%s %d %d %d %d", type, &inputs[0], &inputs[1], &inputs[2], &inputs[3]);
            
            if (strncmp(type, "INPUT", 5) == 0){
                s->gate_type = INPUT_GATE;
                count++;
                inputs[0] = SOURCE_ID;
            } else if (strncmp(type, "OUTPUT", 6) == 0){
                s->gate_type = OUTPUT_GATE;
                s->outputs->size = 1;
                s->outputs->array[0].gid = SINK_ID;
            } else if (strncmp(type, "NOT", 3) == 0){
                s->gate_type = NOT_GATE;
            } else if (strncmp(type, "DFF", 3) == 0){
                s->gate_type = DFF_GATE;
            } else if (strncmp(type, "AND", 3) == 0){
                s->gate_type = AND_GATE;
            } else if (strncmp(type, "NAND", 4) == 0){
                s->gate_type = NAND_GATE;
            } else if (strncmp(type, "OR", 2) == 0){
                s->gate_type = OR_GATE;
            } else if (strncmp(type, "NOR", 3) == 0){
                s->gate_type = NOR_GATE;
            } else if (strncmp(type, "XOR", 3) == 0){
                s->gate_type = XOR_GATE;
            } else if (strncmp(type, "XNOR", 4) == 0){
                s->gate_type = XNOR_GATE;
            } else {
                printf("ERROR: gate type unrecognized in %s", in_msg->data.line);
            }
            
            
            s->inputs->size = count - 1;
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
            
            
            //send message to inputs telling them to output to me
            for (i = 0; i < s->inputs->size; i++) {
                tw_event *e = tw_event_new(s->inputs->array[i].gid, 1, lp);
                message *msg = tw_event_data(e);
                msg->type = SETUP_MSG;
                msg->data.p.gid = self;
                tw_event_send(e);
            }
        }
    } else if (in_msg->type == SETUP_MSG) {
        if (s->outputs->size == MAX_GATE_OUTPUTS) {
            printf("ERROR: %d overflowed output vector\n", self);
        }
        
        s->outputs->array[s->outputs->size].gid = in_msg->data.p.gid;
        s->outputs->size++;
    } else if (in_msg->type == SOURCE_MSG && lp->gid == SOURCE_ID) {
        //s->gate_function(s->inputs, s->outputs);
        int i;
        for (i = 0; i < s->outputs->size; i++) {
            tw_event *e = tw_event_new(s->outputs->array[i].gid, 1, lp);
            message *msg = tw_event_data(e);
            msg->type = LOGIC_CARY_MSG;
            msg->data.p.gid = lp->gid;
            msg->data.p.value = i%2;
            tw_event_send(e);
        }
        
        tw_event *e = tw_event_new(SOURCE_ID, 1, lp);
        message *msg = tw_event_data(e);
        msg->type = SOURCE_MSG;
        tw_event_send(e);
    } else if (self == SINK_ID) {
        //s->gate_func(s->inputs, s->outputs);
        //printf("SUNK\tgid: %d\tval: %d\n", msg->data.gid, msg->data.value);
    } else if (in_msg->type == LOGIC_CARY_MSG) {
        for (i = 0; i < s->inputs->size; i++) {
            if(s->inputs->array[i].gid == in_msg->data.p.gid){
                s->inputs->array[i].value = in_msg->data.p.value;
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
            msg->data.p.gid = lp->gid;
            msg->data.p.value = s->outputs->array[i].value;
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
    
    //IO
    //printf("%d is attempting to start io\n", g_tw_mynode);
    MPI_File fh;
    MPI_Request req;
    
    char filename[100] = "/Users/elsagonsiorowski/Desktop/MY_ROSS/testfile.txt";
    MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
    
    //NOTE: for some reason count is off
    int offset = g_tw_mynode * LP_COUNT * (LINE_LENGTH-1);
    printf("offset is %d\n", offset);
    for (i = 0; i < LP_COUNT; i++) {
        MPI_File_iread_at(fh, offset + (i*LINE_LENGTH) - i, global_input[i], LINE_LENGTH-1, MPI_CHAR, &req);
        //if (g_tw_mynode == 1) printf("<%d read line %s>", g_tw_mynode, global_input[i]);
    }
    MPI_File_close(&fh);
    //printf("%d should have finished io\n", g_tw_mynode);
    
    //printf("lps per pe: %d\n", (int) ceil((2 + TOTAL_GATE_COUNT) / (double)NP));
    tw_define_lps(LP_COUNT, sizeof(message), 0);
    for (i = 0; i < g_tw_nlp; i++) {
        tw_lp_settype(i, &gates_lps[0]);
    }
    
    tw_run();
    
    tw_end();
    
    tw_run();
    
    tw_end();
    
    return 0;
}
