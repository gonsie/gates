//Elsa Gonsiorowski
//October 7, 2011
//Rensselaer Polytechnic Institute

//This file contains the ross functions for the model: init/final, foward/reverse event, mapping, and support

#include <stdio.h>
#include <assert.h>

#include "gates-config.h"
#include "generic-model.h"
#include "library.h"
#include "routing.h"

// #define DEBUG_TRACE 1
#if DEBUG_TRACE
FILE * node_out_file;
#endif

// each PE has its own unique file pointer
FILE * wave_out_file;
double latest_ts = 0.0;

int global_swap_count = 0;
int error_count = 0;

int source_interval = 2;

void SWAP(int *a, int *b) {
    // a ^= b; b ^= a; a ^= b;
    int temp = *a;
    *a = *b;
    *b = temp;
    global_swap_count++;
}

void gates_init(gate_state *s, tw_lp *lp) {
    int self = lp->gid;

    assert(lp->gid == lp->id + (*routing_table_mpi)[g_tw_mynode]);

    if (s->gate_type == input_gate_TYPE) {
        double jitter = (tw_rand_unif(lp->rng)) * 0.1;
        tw_event *e2 = tw_event_new(self, 1 + jitter, lp);
        message *msg2 = tw_event_data(e2);
        msg2->type = SOURCE_MSG;
        msg2->id = self;
        msg2->value = -1;
        tw_event_send(e2);
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
    long start_count = lp->rng->count;

    *(int *) bf = (int) 0;

#if DEBUG_TRACE_RNG
    fprintf(node_out_file, "FWDE: #%u %lu %lu %lu %lu %d %2.3f %u %d\n", self, lp->rng->Cg[0], lp->rng->Cg[1], lp->rng->Cg[2], lp->rng->Cg[3], in_msg->type, tw_now(lp), in_msg->id, global_swap_count);
    fflush(node_out_file);
#endif

    //printf("Processing event type %d on lp %u\n", in_msg->type, self);
    /*
     if (tw_now(lp) >= 29.2) {
     printf("#%u processing event type %d\n", self, in_msg->type);
     }
     */
    //printf("%u processing event %d (%d) rng at %ld at %lf from id %d val %d\n", self, s->received_events, in_msg->type, lp->rng->count, tw_now(lp), in_msg->id, in_msg->value);

    s->received_events++;
    if(lp->id == 0 && error_count != 0){
        tw_error(TW_LOC, "ERROR: %d errors detected in init on node %d\n", error_count, g_tw_mynode);
    }
    assert(error_count == 0);

    if (in_msg->type == SOURCE_MSG) {
        //Assume node 0 is an input //TODO: Can't assume this with partitioning
        if (self == 0) {
            tw_output(lp, "Source nodes doing a wave of inputs at %f.\n", tw_now(lp));
            // printf("Source nodes doing a wave of inputs at %f.\n", tw_now(lp));
        }
        for (i = 0; i < s->output_size; i++) {
            if (s->output_gid[i] >= 0) {
                double delay = g_tw_lookahead;
                double jitter = (tw_rand_unif(lp->rng)) * (1.0 - (2.0 * MESSAGE_PAD));
                delay = MESSAGE_PAD + jitter;
                assert(delay >= g_tw_lookahead);
                tw_event *e = tw_event_new(s->output_gid[i], delay, lp);
                message *msg = tw_event_data(e);
                msg->type = LOGIC_MSG;
                msg->id = s->output_pin[i];
                msg->value = (tw_rand_unif(lp->rng) < 0.5) ? 0 : 1;
                tw_event_send(e);
            }
        }

        double jitter = tw_rand_unif(lp->rng) * 0.1;
        tw_event *e = tw_event_new(self, source_interval + jitter, lp);
        message *msg = tw_event_data(e);
        msg->type = SOURCE_MSG;
        msg->id = self;
        msg->value = -1;
        tw_event_send(e);
    } else if (in_msg->type == LOGIC_MSG) {
        if (s->gate_type == mega_gate_TYPE) {
            goto unified_exit;
        }
        int in_pin = in_msg->id;
        if (s->inputs[in_pin] == in_msg->value) {
            // No state change. event chain dies here
            goto unified_exit;
        }
        BOOL rising = (s->inputs[in_pin] < in_msg->value);
        SWAP(&(s->inputs[in_pin]), &(in_msg->value));

        // store current internal pin state
        if (gate_internal_size[s->gate_type] > 0) {
            assert(gate_internal_size[s->gate_type] == 2 && "ERROR: internal size != 2");
            in_msg->internal_pin0 = s->internals[0];
            in_msg->internal_pin1 = s->internals[1];
        }

        function_array[s->gate_type](s->inputs, s->internals, s->output_val);
        for (i = 0; i < s->output_size; i++){
            if (s->output_gid[i] >= 0) {
                float delay = delay_array[s->gate_type](in_pin, i, rising);
                double jitter = (tw_rand_unif(lp->rng)) * 0.1;
                assert(delay + jitter >= g_tw_lookahead);
                tw_event *e = tw_event_new(s->output_gid[i], delay + jitter, lp);
                message *msg = tw_event_data(e);
                msg->type = LOGIC_MSG;
                msg->id = s->output_pin[i];
                msg->value = s->output_val[i];
                tw_event_send(e);
            }
        }

        if (s->wave_print) {
            // assume OUTPUT_gate type
            wave_print(tw_now(lp), s->inputs[0], s->wave_id);
        }
    } else if (in_msg->type == WAVE_MSG) {
        if (self != 0) {
            // turn on wave printing for this LP
            SWAP(&(s->wave_print), &(in_msg->value));
            s->wave_id = (char) in_msg->id;
        }
    } else {
        printf("ERROR: could not process message type %d on lp %u\n", in_msg->type, self);
    }
unified_exit:
    in_msg->rng_count = lp->rng->count - start_count;
}

void gates_event_rc(gate_state *s, tw_bf *bf, message *in_msg, tw_lp *lp){
    int i;
    unsigned int self = lp->gid;
    long count;

    s->received_events--;
    s->roll_backs++;
    //printf("%u reversing %d\n", self, in_msg->type);
    //fflush(stdout);
    assert(in_msg->type >= 0);
    if (in_msg->type == LOGIC_MSG) {
        if (s->gate_type == mega_gate_TYPE) {
            goto unified_exit_rc;
        }
        if (s->inputs[in_msg->id] == in_msg->value){
            goto unified_exit_rc;
        }
        SWAP(&(s->inputs[in_msg->id]), &(in_msg->value));

        // store current internal pin state
        if (gate_internal_size[s->gate_type] > 0) {
            assert(gate_internal_size[s->gate_type] == 2 && "ERROR: internal size != 2");
            s->internals[0] = in_msg->internal_pin0;
            s->internals[1] = in_msg->internal_pin1;
        }

    } else if (in_msg->type == WAVE_MSG) {
        if (self != 0){
            SWAP(&(s->wave_print), &(in_msg->value));
        }
    }
unified_exit_rc:
    count = in_msg->rng_count;
    while (count--) {
        tw_rand_reverse_unif(lp->rng);
    }
    //printf("%d un-processed %d (%d) rng at %ld at %lf from id %d val %d\n", self, s->received_events, in_msg->type, lp->rng->count, tw_now(lp), in_msg->id, in_msg->value);
#if DEBUG_TRACE_RNG
    fprintf(node_out_file, "REVE: #%u %lu %lu %lu %lu %d %2.3f %u %d\n", self, lp->rng->Cg[0], lp->rng->Cg[1], lp->rng->Cg[2], lp->rng->Cg[3], in_msg->type, tw_now(lp), in_msg->data.gid, global_swap_count);
    fflush(node_out_file);
#endif

}

void gates_final(gate_state *s, tw_lp *lp){
    unsigned int self = lp->gid;

#if DEBUG_TRACE
    fprintf(node_out_file, "FINAL: #%u type:%d net:%d\n", self, s->gate_type, s->received_events);
    fflush(node_out_file);
#endif
    if(FALSE) {
        printf("#%u e%d\n", self, s->received_events);
        fflush(stdout);
    }
    return;
}
