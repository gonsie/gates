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

const tw_optdef gates_opts[] = {
    TWOPT_GROUP("Gates Model"),
    TWOPT_UINT("source_interval", source_interval,"time between source sending waves of input"),
    TWOPT_UINT("sink_interval", sink_interval, "time between reporting of sink statistics"),
    TWOPT_END(),
};

extern unsigned int nkp_per_pe;

#define gates_main main

int gates_main(int argc, char* argv[]){
    
    int i;
        
    tw_opt_add(gates_opts);
    tw_init(&argc, &argv);
    
    if (tw_nnodes() != GLOBAL_NP_COUNT) {
        printf("ERROR: expected %d processors but %d were defined\n", GLOBAL_NP_COUNT, tw_nnodes());
        return 1;
    }

    
    g_tw_mapping = CUSTOM;
    g_tw_custom_initial_mapping = &gates_custom_round_robin_mapping_setup;
    g_tw_custom_lp_global_to_local_map = &gates_custom_round_robin_mapping_to_local;
    
    g_tw_events_per_pe = LP_COUNT * MAX_GATE_INPUTS + SOURCE_OUTPUTS * 2 + 32000;
    g_tw_lookahead = 0.09;
    
    //My kp count
    g_tw_nkp = 64;
    
    //My lp count
    g_tw_nlp = LP_COUNT;
    
    instance_node = g_tw_mynode % INSTANCE_NP_COUNT;
    if (instance_node < EXTRA_LP_COUNT) {
        g_tw_nlp++;
    }
    
    instance_id = g_tw_mynode / INSTANCE_NP_COUNT;
    instance_x = instance_id % X_COUNT;
    instance_y = instance_id / X_COUNT;
    instance_0 = instance_id * TOTAL_GATE_COUNT;    
    
    printf("Node %d: instance_id=%d, instance_node=%d, instance_x=%d, instance_y=%d\n", g_tw_mynode, instance_id, instance_node, instance_x, instance_y);
    
    tw_define_lps(g_tw_nlp, sizeof(message), 0);
    for (i = 0; i < g_tw_nlp; i++) {
        tw_lp_settype(i, &gates_lps[0]);
    }
    
    char filename[100] = "/data.vbench";
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
        //IO
        //printf("%d is attempting to start io\n", g_tw_mynode);
        MPI_File fh;
        MPI_Status req;
        
        MPI_File_open(MPI_COMM_WORLD, fullpath, MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
        
        //NOTE: for some reason count is off
        int line_start, line_end;
        int current_id;
        if (instance_node == 0) {
            line_start = 0;
        } else {
            line_start = (instance_node * LP_COUNT) + min(instance_node, EXTRA_LP_COUNT);
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

