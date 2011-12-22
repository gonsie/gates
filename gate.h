//Elsa Gonsiorowski
//October 7, 2011
//Rensselaer Polytechnic Institute


//Settings for individual gates


#ifndef _gate_h
#define _gate_h

#include <stdarg.h>
#include "ptwHeader.h"

typedef char* string;


typedef struct {
    int gid;
    int value;
} pair;

typedef struct vector {
    int size;
    pair array[];
} *vector;


union message_data {
    pair p;
    char line[LINE_LENGTH];
};


typedef struct {
    int type;
    union message_data data;
} message;



typedef void (*gate_func)(vector input, vector output);
//assuming boolean (0/1) logic for now

void SOURCE_func(vector input, vector output){
}

void SINK_func(vector input, vector output){
    int i;
    for(i = 0; i < input->size; i++){
        printf("Received a %d, supposedly from gate with id %d.\n", input->array[i].value, input->array[i].gid);
    }
}

void INPUT_func(vector input, vector output){
    int i;
    for (i = 0; i < input->size; i++) {
        output->array[i].value = input->array[i].value;
    }
}

void OUTPUT_func(vector input, vector output){
    int i;
    for (i = 0; i < input->size; i++) {
        output->array[i].value = input->array[i].value;
    }
}

void NOT_func(vector input, vector output){
    int i;
    for(i = 0; i < input->size; i++){
        if (input->array[i].value) {
            output->array[i].value = FALSE;
        } else {
            output->array[i].value = TRUE;
        }
    }
}

void DFF_func(vector input, vector output){
    int i;
    for (i = 0; i < input->size; i++) {
        output->array[i].value = input->array[i].value;
    }
}

void AND_func(vector input, vector output){
    int i;
    for(i = 0; i < input->size; i++){
        if (!input->array[i].value) {
            output->array[0].value = FALSE;
            return;
        }
    }
    output->array[0].value = TRUE;
}

void NAND_func(vector input, vector output){
    AND_func(input, output);
    NOT_func(output, output);
}

void OR_func(vector input, vector output){
    int i;
    for (i = 0; i < input->size; i++) {
        if (input->array[i].value) {
            output->array[0].value = TRUE;
            return;
        }
    }
    output->array[0].value = FALSE;
}

void NOR_func(vector input, vector output){
    OR_func(input, output);
    NOT_func(output, output);
}

void XOR_func(vector input, vector output){
    int i, count;
    for (i = 0, count = 0; i < input->size; i++) {
        if (input->array[i].value) {
            count++;
        }
    }
    if (count % 2 == 1) {
        output->array[0].value = TRUE;
    } else {
        output->array[0].value = FALSE;
    }
}

void XNOR_func(vector input, vector output){
    XOR_func(input, output);
    NOT_func(output, output);
}





typedef struct {
    
    //gate specific information
    int gate_type;
    
    //variables for linking gates
    vector inputs;
    vector outputs;
    
    int received_events;
    
} gate_state;

#endif
