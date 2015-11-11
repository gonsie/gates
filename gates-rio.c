//Elsa Gonsiorowski
//October 31, 2015
//Rensselaer Polytechnic Institute

#include "generic-model.h"
#include "library.h"

size_t gate_size (gate_state *s, tw_lp *lp) {
	size_t sum_size = sizeof(gate_state);

	// DO INTERNALS FIRST
	// s->internals array
	sum_size += sizeof(int) * gate_internal_size[s->gate_type];

	// s->inputs array
	int in_size;
	if (s->gate_type == mega_gate_TYPE) {
		in_size = s->internals[0];
	} else {
		in_size = gate_input_size[s->gate_type];
	}
	sum_size += sizeof(int) * in_size;

	// s->output_[gid,pin,val] arrays
	sum_size += sizeof(int) * s->output_size * 3;

    return sum_size;
}

void gate_serialize (gate_state *s, void * buffer, tw_lp *lp) {
	size_t offset = 0;

	// gate state
    memcpy(buffer, s, sizeof(gate_state));
    offset += sizeof(gate_state);

    // DO INTERNALS FIRST
	// s->internals array
	memcpy(buffer+offset, s->internals, sizeof(int) * gate_internal_size[s->gate_type]);
	offset += sizeof(int) * gate_internal_size[s->gate_type];

    // s->inputs array
	int in_size;
	if (s->gate_type == mega_gate_TYPE) {
		in_size = s->internals[0];
	} else {
		in_size = gate_input_size[s->gate_type];
	}
	memcpy(buffer+offset, s->inputs, sizeof(int) * in_size);
	offset += sizeof(int) * in_size;

	// 3x s->outputs arrays
	memcpy(buffer+offset, s->output_gid, sizeof(int) * s->output_size);
	offset += sizeof(int) * s->output_size;

	memcpy(buffer+offset, s->output_pin, sizeof(int) * s->output_size);
	offset += sizeof(int) * s->output_size;

	memcpy(buffer+offset, s->output_val, sizeof(int) * s->output_size);
	offset += sizeof(int) * s->output_size;

    return;
}

void gate_deserialize (gate_state *s, void *buffer, tw_lp *lp) {
	size_t offset = 0;

	// gate state
	memcpy(s, buffer, sizeof(gate_state));
	offset += sizeof(gate_state);

	// DO INTERNALS FIRST
	// s->internals array
	s->internals = tw_calloc(TW_LOC, "gates_init_gate_internal", sizeof(int), gate_internal_size[s->gate_type]);
	memcpy(s->internals, buffer+offset, sizeof(int) * gate_internal_size[s->gate_type]);
	offset += sizeof(int) * gate_internal_size[s->gate_type];

	// s->inputs array
	int in_size;
	if (s->gate_type == mega_gate_TYPE) {
		in_size = s->internals[0];
	} else {
		in_size = gate_input_size[s->gate_type];
	}
	s->inputs = tw_calloc(TW_LOC, "gates_init_gate_input", sizeof(int), in_size);
    memcpy(s->inputs, buffer+offset, sizeof(int) * in_size);
	offset += sizeof(int) * in_size;

	// 3x s->outputs arrays
	s->output_gid = tw_calloc(TW_LOC, "gates_init_gate_output", sizeof(int), s->output_size);
    memcpy(s->output_gid, buffer+offset, sizeof(int) * s->output_size);
	offset += sizeof(int) * s->output_size;

	s->output_pin = tw_calloc(TW_LOC, "gates_init_gate_output", sizeof(int), s->output_size);
    memcpy(s->output_pin, buffer+offset, sizeof(int) * s->output_size);
	offset += sizeof(int) * s->output_size;

	s->output_val = tw_calloc(TW_LOC, "gates_init_gate_output", sizeof(int), s->output_size);
    memcpy(s->output_val, buffer+offset, sizeof(int) * s->output_size);
	offset += sizeof(int) * s->output_size;

    return;
}

