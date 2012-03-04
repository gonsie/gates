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

extern gate_func function_array[];


//assuming boolean (0/1) logic for now
//function returns true or false if the output value has changed


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
