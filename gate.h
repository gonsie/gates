//Elsa Gonsiorowski
//October 7, 2011
//Rensselaer Polytechnic Institute

//Header for a specific gate library. #def's for specific gates

#ifndef _gate_h
#define _gate_h

#define SOURCE_OUTPUTS 3305
#define SINK_INPUTS 3205
#define MAX_GATE_INPUTS 4
#define MAX_GATE_OUTPUTS 5214

//Gate Types
#define GATE_TYPE_COUNT (12)
#define SOURCE_GATE (0)
#define SINK_GATE (1)
#define INPUT_GATE (2)
#define OUTPUT_GATE (3)
#define NOT_GATE (4)
#define DFF_GATE (5)
#define AND_GATE (6)
#define NAND_GATE (7)
#define OR_GATE (8)
#define NOR_GATE (9)
#define XOR_GATE (10)
#define XNOR_GATE (11)

#define SOURCE_ID (-1)
#define SINK_ID (-2)

#endif


