//Elsa Gonsiorowski
//October 7, 2011
//Rensselaer Polytechnic Institute

//The main function and command line arguments

#include <stdio.h>
#include <libgen.h>
#include <assert.h>

#include "gates-config.h"
#include "generic-model.h"
#include "routing.h"

//#define VERIFY_READ 1
intarrptr routing_table_mpi;

const tw_optdef gates_opts[] = {
    TWOPT_GROUP("Gates Model"),
    TWOPT_END(),
};

tw_lptype gates_lps[] = {
    {   (init_f) gates_init,
        (pre_run_f) NULL,
        (event_f) gates_event,
        (revent_f) gates_event_rc,
        (commit_f) NULL,
        (final_f) gates_final,
        (map_f) gates_custom_mapping_to_pe,
        sizeof(gate_state)  },
    { 0 },
};

io_lptype iolps[] = {
    {(serialize_f) gate_serialize,
     (deserialize_f) gate_deserialize,
     (model_size_f) gate_size},
    {0},
};

#define gates_main main

int gates_main(int argc, char* argv[]){

    int i, j;

    tw_opt_add(gates_opts);
    tw_init(&argc, &argv);

    // if (WAVE_COUNT != 0 && g_tw_synchronization_protocol > 2) {
    //     printf("ERROR: Waveform viewing is not supported for non-conservative protocols.\n");
    //     return 1;
    // }

    g_tw_mapping = CUSTOM;
    g_tw_custom_initial_mapping = &gates_custom_mapping_setup;
    g_tw_custom_lp_global_to_local_map = &gates_custom_mapping_to_local;
    routing_table_mpi = routing_table_mapper(tw_nnodes());

    g_tw_lp_offset = (*routing_table_mpi)[g_tw_mynode];
    g_tw_nlp = (*routing_table_mpi)[g_tw_mynode+1] - g_tw_lp_offset;
    g_tw_nkp = TOTAL_PARTS / tw_nnodes();
    if (g_tw_mynode < TOTAL_PARTS - (g_tw_nkp * tw_nnodes())) {
        g_tw_nkp++;
    }

    g_tw_events_per_pe = 100*g_tw_nlp;
    g_tw_lookahead = 0.001;

    tw_define_lps(g_tw_nlp, sizeof(message));

    g_tw_lp_types = gates_lps;
    g_io_lp_types = iolps;
    tw_lp_setup_types();

    g_io_events_buffered_per_rank = 0;
    char cpname[100];
    char *dpath = dirname(argv[0]);
    sprintf(cpname, "%s/checkpoint/submodule-checkpoint", dpath);
    io_init();
    io_load_checkpoint(cpname, PRE_INIT);

#if DEBUG_TRACE
    char debugfile[100];
    sprintf(debugfile, "%s/debug/node_%d_output_file.txt", dpath, g_tw_mynode);
    node_out_file = fopen(debugfile,"w");
#endif

    tw_run();

    tw_end();

    return 0;
}

