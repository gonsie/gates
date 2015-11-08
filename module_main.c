//Elsa Gonsiorowski
//October 7, 2011
//Rensselaer Polytechnic Institute

//The main function and command line arguments

#include <stdio.h>
#include <libgen.h>
#include <assert.h>

#include "ross.h"
#include "gates_model.h"
#include "library.h"
#include "routing.h"

//#define VERIFY_READ 1
#define LPS_PER_KP (18)
#define TOTAL_PARTS (329474)

unsigned int module_index = 0;
unsigned int use_unique_name_flag = 0;
unsigned int ml_op = 0;

FILE * global_datafile_handle;
long global_datafile_offset = 0;
char global_datafile_buffer[513];

// EMPTY FUNCTIONS
void gate_init(gate_state *s, tw_lp *lp) {
    int i;

    // Load buffer starting at offset
    global_datafile_buffer[512] = '\0';
    fseek(global_datafile_handle, global_datafile_offset, SEEK_SET);

    size_t amt_read;
    int gid, type;
    int offset;
    char * line;
    int total_offset = 0;

    amt_read = fread(global_datafile_buffer, sizeof(char), 512, global_datafile_handle);
    // TODO : EOF error handling?

    line = global_datafile_buffer;
    int count = sscanf(line, "%d %d %n", &gid, &type, &offset);
#if VERIFY_READ
    printf("\nScan Found: GID %d TYPE %d ", gid, type);
#endif
    line += offset;
    global_datafile_offset += offset;
    total_offset += offset;

    assert(gid == lp->id && "ERROR: wrong lp id");

    s->gate_type = type;

    // IN OUT SIZE SPECIAL CASES
    int in_size, out_size;
    if (s->gate_type == fanout_TYPE) {
        sscanf(line, "%d %n", &out_size, &offset);
#if VERIFY_READ
        printf("FAN_OUT_SIZE %d, ", out_size);
#endif
        line += offset;
        global_datafile_offset += offset;
        total_offset += offset;
        in_size = 1;
    } else if (s->gate_type == mega_gate_TYPE) {
        sscanf(line, "%d %d %n", &in_size, &out_size, &offset);
#if VERIFY_READ
        printf("MEGA_IN_SIZE %d, MEGA_OUT_SIZE %d, ", in_size, out_size);
#endif
        line += offset;
        global_datafile_offset += offset;
        total_offset += offset;
    } else {
        in_size = gate_input_size[s->gate_type];
        out_size = gate_output_size[s->gate_type];
    }

    // INIT input array
    s->inputs = tw_calloc(TW_LOC, "gates_init_gate_input", in_size * sizeof(int), 1);
    for (i = 0; i < in_size; i++) {

        if (total_offset > 500) {
            fseek(global_datafile_handle, global_datafile_offset, SEEK_SET);
            fread(global_datafile_buffer, sizeof(char), 512, global_datafile_handle);
            line = global_datafile_buffer;
            total_offset = 0;
        }

        // Test for constants
        if (strncmp(line, "#", 1) == 0) {
            int constant;
            sscanf(line, "#%d %n", &constant, &offset);
#if VERIFY_READ
            printf("CONST %d ", constant);
#endif
            line += offset;
            global_datafile_offset += offset;
            total_offset += offset;
            // TODO: some how mark this as not a GID
            s->inputs[i] = constant;
        } else {
            int module, from_gid;
            sscanf(line, "%d %n", &module, &offset);
#if VERIFY_READ
            printf("in %d, ", module);
#endif
            line += offset;
            global_datafile_offset += offset;
            total_offset += offset;
            if (strncmp(line, ".", 1) == 0) {
                sscanf(line+1, "%d %n", &from_gid, &offset);
                from_gid += routing_table[module];
#if VERIFY_READ
                printf("routing %d, ", from_gid);
#endif
                line += offset+1;
                global_datafile_offset += offset+1;
                total_offset += offset+1;
            } else {
                from_gid = module;
            }
            if (from_gid >= 0) {
                s->inputs[i] = routing_table[module_index] + from_gid;
            }
        }
    }

    // INIT internal array
    s->internals = tw_calloc(TW_LOC, "gates_init_gate_internal", gate_internal_size[s->gate_type] * sizeof(int), 1);

    // HACK!! Needed for fanout gate_func
    if (s->gate_type == fanout_TYPE) {
        s->internals[0] = out_size;
    }
    // HACK!! Needed for mega_gate RIO sizing
    if (s->gate_type == mega_gate_TYPE) {
        s->internals[0] = in_size;
    }

    // INIT output array
    s->output_size = out_size;

    s->output_gid = tw_calloc(TW_LOC, "gates_init_gate_output", s->output_size * sizeof(int), 1);
    s->output_pin = tw_calloc(TW_LOC, "gates_init_gate_output", s->output_size * sizeof(int), 1);
    s->output_val = tw_calloc(TW_LOC, "gates_init_gate_output", s->output_size * sizeof(int), 1);
    for (i = 0; i < s->output_size; i++) {
        s->output_gid[i] = -1;
        s->output_pin[i] = -1;
        s->output_val[i] = -1;
    }

    for (i = 0; i < s->output_size; i++) {

        if (total_offset > 490) {
            fseek(global_datafile_handle, global_datafile_offset, SEEK_SET);
            fread(global_datafile_buffer, sizeof(char), 512, global_datafile_handle);
            line = global_datafile_buffer;
            total_offset = 0;
        }

        int module, to_gid, to_pin;
        sscanf(line, "%d%n", &module, &offset);
#if VERIFY_READ
        printf("out %d ", module);
#endif
        line += offset;
        global_datafile_offset += offset;
        total_offset += offset;
        if (strncmp(line, ".", 1) == 0) {
            sscanf(line+1, "%d %n", &to_gid, &offset);
#if VERIFY_READ
            printf("ROUTE %d (%d)", to_gid, routing_table[module]);
#endif
            to_gid += routing_table[module];
            line += offset+1;
            global_datafile_offset += offset+1;
            total_offset += offset+1;
        } else {
            to_gid = module;
        }

        assert(1 == sscanf(line, "%d %n", &to_pin, &offset) && "ERROR: expected pindex");
#if VERIFY_READ
        printf("PIN %d, ", to_pin);
#endif
        line += offset;
        global_datafile_offset += offset;
        total_offset += offset;
        if (to_gid >= 0) {
            s->output_gid[i] = to_gid;
            s->output_pin[i] = to_pin;
        }
    }
#if VERIFY_READ
    printf("\n");
#endif
    return;
}

void blank_event_handler(gate_state *s, tw_bf *bf, message *in_msg, tw_lp *lp){
    return;
}

void blank_event_handler_rc(gate_state *s, tw_bf *bf, message *in_msg, tw_lp *lp){
    return;
}

void blank_finish(gate_state *s, tw_lp *lp){
    return;
}

const tw_optdef module_loader_opts[] = {
    TWOPT_GROUP("Module Loader"),
    TWOPT_UINT("index", module_index,"index of submodule to be loaded"),
    TWOPT_UINT("uname", use_unique_name_flag, "use a unique name for each module file"),
    TWOPT_UINT("op", ml_op, "operation selector. 0 = load ascii, store RIO; 1 = load RIO"),
    TWOPT_END(),
};

tw_peid module_loader_map(tw_lpid gid) {
    return (tw_peid) 0;
}

void module_loader_mapping_setup(void){
    int lpid, kpid;
    int i;
    tw_pe *pe = tw_pe_next(NULL);

    int extra_lp_on_kp = g_tw_nlp - (g_tw_nkp * LPS_PER_KP);

    for (lpid = 0, kpid = 0; kpid < g_tw_nkp; kpid++) {
        tw_kp_onpe(kpid, pe);

        int lps_on_kp = LPS_PER_KP;
        if (kpid < extra_lp_on_kp) {
            lps_on_kp++;
        }

        for (i = 0; i < lps_on_kp; i++, lpid++) {
            tw_lp_onpe(lpid, pe, lpid);
            tw_lp_onkp(g_tw_lp[lpid], g_tw_kp[kpid]);
        }
    }
    return;
}

tw_lp * module_loader_mapping_to_local(tw_lpid lpid){
    return g_tw_lp[lpid];
}

tw_lptype mylps[] = {
    {(init_f) gate_init,
     (pre_run_f) NULL,
     (event_f) blank_event_handler,
     (revent_f) blank_event_handler_rc,
     (final_f) blank_finish,
     (map_f) module_loader_map,
    sizeof(gate_state)},
    {0},
};

io_lptype iolps[] = {
    {(serialize_f) gate_serialize,
     (deserialize_f) gate_deserialize,
     (model_size_f) gate_size},
    {0},
};


#define module_loader_main main

int module_loader_main(int argc, char* argv[]){

    int i, j;

    tw_opt_add(module_loader_opts);
    tw_init(&argc, &argv);

    if (tw_nnodes() != 1) {
        printf("ERROR: Module Loader expects 1 MPI-Rank, found %d\n", tw_nnodes());
        return 1;
    }

    g_tw_mapping = CUSTOM;
    g_tw_custom_initial_mapping = &module_loader_mapping_setup;
    g_tw_custom_lp_global_to_local_map = &module_loader_mapping_to_local;

    module_index += g_tw_mynode;
    printf("Rank %ld loading Module %d\n", g_tw_mynode, module_index);

    g_tw_nlp = routing_table[module_index+1] - routing_table[module_index];
    g_tw_nkp = g_tw_nlp / LPS_PER_KP;

    tw_define_lps(g_tw_nlp, sizeof(message), 0);

    g_tw_lp_types = mylps;
    g_io_lp_types = iolps;
    tw_lp_setup_types();

    g_io_events_buffered_per_rank = 0;
    io_init_local(g_tw_nkp);

    char dataname[100];
    char *datapath = dirname(argv[0]);
    int file_num = g_tw_mynode+module_index;
    sprintf(dataname, "%s/data-%d.vbench", datapath, file_num);

    // each rank reads its own file
    global_datafile_handle = fopen(dataname, "r");

    tw_run();

    fclose(global_datafile_handle);

    if (use_unique_name_flag == 1) {
        char checkpointname[50];
        sprintf(checkpointname, "module-%03d.checkpoint", file_num);
        io_store_multiple_partitions(checkpointname, 0, 0);
    } else {
        io_store_multiple_partitions("submodule-checkpoint", 1, file_num);
    }

    tw_end();

    return 0;
}
