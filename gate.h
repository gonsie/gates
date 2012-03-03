//Elsa Gonsiorowski
//October 7, 2011
//Rensselaer Polytechnic Institute


//Settings for individual gates


#ifndef _gate_h
#define _gate_h

#include <stdarg.h>
#include "ptwHeader.h"

typedef char* string;


typedef struct pair_t {
    int gid;
    int value;
} pair;

typedef struct vector_t {
    int size;
    pair array[];
} *vector;

typedef struct {
    int type;
    pair data;
} message;



typedef int (*gate_func)(vector input, vector output);
//assuming boolean (0/1) logic for now
//function returns true or false if the output value has changed

int SOURCE_func(vector input, vector output){
    return 0;
}

int SINK_func(vector input, vector output){
    int i;
    for(i = 0; i < input->size; i++){
      //printf("Received a %d, supposedly from gate with id %d.\n", input->array[i].value, input->array[i].gid);
    }
    return 0;
}

int INPUT_func(vector input, vector output){
    int change_flag = FALSE;
    if (output->array[0].value != input->array[0].value) {
        change_flag = TRUE;
    }
    
    //size is expected to be 1
    int i;
    for (i = 0; i < input->size; i++) {
        output->array[i].value = input->array[i].value;
    }
    
    return change_flag;
}

int OUTPUT_func(vector input, vector output){
    int change_flag = FALSE;
    if (output->array[0].value != input->array[0].value) {
        change_flag = TRUE;
    }
    
    //size is expected to be 1
    int i;
    for (i = 0; i < input->size; i++) {
      //output->array[i].value = input->array[i].value;
    }
    
    return change_flag;
}

int NOT_func(vector input, vector output){
    int change_flag = FALSE;
    if (output->array[0].value == input->array[0].value) {
        change_flag = TRUE;
    }
    
    //size is expected to be 1
    int i;
    for(i = 0; i < input->size; i++){
        output->array[i].value = LOGIC_NOT(input->array[i].value);
    }
    
    return change_flag;
}

int DFF_func(vector input, vector output){
    int change_flag = FALSE;
    if (output->array[0].value != input->array[0].value) {
        change_flag = TRUE;
    }
    
    //size is expected to be 1
    int i;
    for (i = 0; i < input->size; i++) {
        output->array[i].value = input->array[i].value;
    }
    
    return change_flag;
}

int AND_func(vector input, vector output){
    int i;
    for(i = 0; i < input->size; i++){
        if (!input->array[i].value) {
            if (output->array[0].value == FALSE) {
                return FALSE;
            } else {
                output->array[0].value = FALSE;
                return TRUE;
            }
        }
    }
    if (output->array[0].value == TRUE) {
        return FALSE;
    } else {
        output->array[0].value = TRUE;
        return TRUE;
    }
}

int NAND_func(vector input, vector output){
    int and_change = AND_func(input, output);
    NOT_func(output, output);
    return LOGIC_NOT(and_change);
}

int OR_func(vector input, vector output){
    int i;
    for (i = 0; i < input->size; i++) {
        if (input->array[i].value) {
            if (output->array[0].value == TRUE) {
                return FALSE;
            } else {
                output->array[0].value = TRUE;
                return TRUE;
            }
        }
    }
    if (output->array[0].value == FALSE) {
        return FALSE;
    } else {
        output->array[0].value = FALSE;
        return TRUE;
    }
}

int NOR_func(vector input, vector output){
    int or_change = OR_func(input, output);
    NOT_func(output, output);
    return LOGIC_NOT(or_change);
}

int XOR_func(vector input, vector output){
    int i, count;
    for (i = 0, count = 0; i < input->size; i++) {
        if (input->array[i].value) {
            count++;
        }
    }
    
    if (output->array[0].value != count % 2) {
        output->array[0].value = count % 2;
        return TRUE;
    }
    return FALSE;
}

int XNOR_func(vector input, vector output){
    int xor_change = XOR_func(input, output);
    NOT_func(output, output);
    return LOGIC_NOT(xor_change);
}

typedef struct {
    
    //gate specific information
    int gate_type;
    
    //variables for linking gates
    vector inputs;
    vector outputs;
    
    int received_events;
    int calc;
    int stat_output_change;
    
} gate_state;

#endif
