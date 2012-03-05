//Elsa Gonsiorowski
//October 7, 2011
//Rensselaer Polytechnic Institute

//The main function and command line arguments

#include <stdio.h>
#include <libgen.h>

#include "ross.h"
#include "run_config.h"
#include "gates_model.h"
#include "gate.h"

unsigned int source_interval = 1;
unsigned int sink_interval = 5;

const tw_optdef gates_opts[] = {
    TWOPT_GROUP("Gates Model"),
    TWOPT_UINT("source_interval", source_interval,"time between source sending waves of input"),
    TWOPT_UINT("sink_interval", sink_interval, "time between reporting of sink statistics"),
    TWOPT_END(),
};

#define gates_main main

int gates_main(int argc, char* argv[]){
    
    int i;
    
    //g_tw_nkp = 1;
    
    tw_opt_add(gates_opts);
    
    tw_init(&argc, &argv);
    
    
    
    g_tw_mapping = CUSTOM;
    g_tw_custom_initial_mapping = &gates_custom_mapping;
    g_tw_custom_lp_global_to_local_map = &gates_mapping_to_lp;
    
    g_tw_events_per_pe = LP_COUNT * MAX_GATE_INPUTS + SOURCE_OUTPUTS * 2 + 32000;
    g_tw_lookahead = 0.09;
    
    g_tw_nlp = LP_COUNT;
    if (g_tw_mynode < EXTRA_LP_COUNT) {
        g_tw_nlp++;
    }
    
    tw_define_lps(g_tw_nlp, sizeof(message), 0);
    for (i = 0; i < g_tw_nlp; i++) {
        tw_lp_settype(i, &gates_lps[0]);
    }
    
    
    
    char filename[100] = "/ccx_mpi.bench";
    char *fullpath = dirname(argv[0]);
    strcat(fullpath, filename);
    if (g_tw_synchronization_protocol == 1) {
        //sequential
        FILE *my_file = fopen(fullpath, "r");
        for (i = 0; i < LP_COUNT; i++) {
            fgets(global_input[i], LINE_LENGTH, my_file);
        }
        fclose(my_file);
    } else {
        //Error checking
        int np;
        int rc = MPI_Comm_size(MPI_COMM_WORLD, &np);
        printf("(%d)", rc);
        if (np != NP_COUNT) {
            printf("ERROR: expected %d processors but %d were defined\n", NP_COUNT, np);
            return 1;
        }
        
        //IO
        //printf("%d is attempting to start io\n", g_tw_mynode);
        MPI_File fh;
        MPI_Status req;
        
        MPI_File_open(MPI_COMM_WORLD, fullpath, MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
        
        //NOTE: for some reason count is off
        int line_start, line_end;
        int current_id;
        if (g_tw_mynode == 0) {
            line_start = 0;
        } else {
            line_start = (g_tw_mynode * LP_COUNT) + min(g_tw_mynode, EXTRA_LP_COUNT);
        }
        line_end = line_start + g_tw_nlp;
        current_id = 0;
        
        if (line_end > TOTAL_GATE_COUNT) {
            printf("ERROR: %d wants to read extra lines\n", g_tw_mynode);
            line_end = TOTAL_GATE_COUNT;
        }
        //printf("node %d starting at line %d and ending at line %d\n", (int) g_tw_mynode, line_start, line_end);
        for (i = line_start; i < line_end; i++, current_id++) {
            MPI_File_read_at(fh, i * (LINE_LENGTH - 1), global_input[current_id], LINE_LENGTH-1, MPI_CHAR, &req);
        }
        MPI_File_close(&fh);
    }
    
#if DEBUG_TRACE
    if (g_tw_mynode == 0) {
        node_out_file = fopen("node_0_output_file.txt","w");
    } else if (g_tw_mynode == 1) {
        node_out_file = fopen("node_1_output_file.txt", "w");
    } else if (g_tw_mynode == 2) {
        node_out_file = fopen("node_2_output_file.txt", "w");
    } else if (g_tw_mynode == 4) {
        node_out_file = fopen("node_4_output_file.txt", "w");
    }
#endif
    
    tw_run();
    
    tw_end();
    
    return 0;
}

