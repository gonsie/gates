//Elsa Gonsiorowski
//October 7, 2011
//Rensselaer Polytechnic Institute

//The main function and command line arguments

#include <stdio.h>
#include <libgen.h>
#include <assert.h>

#include "ross.h"
#include "run_config.h"
#include "gates_model.h"
#include "gate.h"

const tw_optdef gates_opts[] = {
    TWOPT_GROUP("Gates Model"),
    TWOPT_UINT("source_interval", source_interval,"time between source sending waves of input"),
    TWOPT_UINT("sink_interval", sink_interval, "time between reporting of sink statistics"),
    TWOPT_UINT("capture", capture, "gid for waveform capture"),
    TWOPT_END(),
};

extern unsigned int nkp_per_pe;

#define gates_main main

int gates_main(int argc, char* argv[]){
    
    int i, j;
        
    tw_opt_add(gates_opts);
    tw_init(&argc, &argv);
    
    if (tw_nnodes() != GLOBAL_NP_COUNT) {
        printf("ERROR: expected %d processors but %d were defined\n", GLOBAL_NP_COUNT, tw_nnodes());
        return 1;
    }
    
    if (g_tw_mynode == 0) {
        printf("Gates Configuration:\n\t");
        printf("X_COUNT = %d * Y_COUNT = %d => COPY_COUNT = %d\n\t", X_COUNT, Y_COUNT, COPY_COUNT);
        printf("NP_PER_INSTANCE = %d --or-- INSTANCE_PER_NP = %d\n\t", NP_PER_INSTANCE, INSTANCE_PER_NP);
        printf("TOTAL_GATE_COUNT = %d, LP_COUNT = %d\n", TOTAL_GATE_COUNT, LP_COUNT);
    }
    
    g_tw_mapping = CUSTOM;
    g_tw_custom_initial_mapping = &gates_custom_round_robin_mapping_setup;
    g_tw_custom_lp_global_to_local_map = &gates_custom_round_robin_mapping_to_local;
    
    g_tw_events_per_pe = 600000;
    g_tw_lookahead = MESSAGE_PAD;
    
    //My kp count
    g_tw_nkp = 64;
    
    //My lp count
    g_tw_nlp = LP_COUNT;
    
    int instnode = 0;
    if (NP_PER_INSTANCE > 0) {
        //g_tw_events_per_pe /= NP_PER_INSTANCE;    //you can't have too many events
        instnode = g_tw_mynode % NP_PER_INSTANCE;
        if (instnode < EXTRA_LP_COUNT) {
            g_tw_nlp++;
        }
    } else if (INSTANCE_PER_NP > 0){
        //g_tw_events_per_pe *= INSTANCE_PER_NP;
        g_tw_nlp *= INSTANCE_PER_NP;
    } else {
        printf("Error: Both INSTANCE_PER_NP and NP_PER_INSTANCE are false\n");
    }
    
    tw_define_lps(g_tw_nlp, sizeof(message), 0);
    for (i = 0; i < g_tw_nlp; i++) {
        tw_lp_settype(i, &gates_lps[0]);
    }
    
    // int fnum = g_tw_mynode % X_COUNT;
    // char filelead[10] = "/data_";
    // char fileend[10] = ".vbench";
    // char filename[100];
    // sprintf(filename, "%s%d%s", filelead, fnum, fileend);
    char filename[100] = "/data.vbench";
    char *fullpath = dirname(argv[0]);
    strcat(fullpath, filename);
    
    //single processor, single file
    if (g_tw_synchronization_protocol == 1) {
        //sequential
        FILE *my_file = fopen(fullpath, "r");
        for (i = 0; i < LP_COUNT; i++) {
            fgets(global_input[i], LINE_LENGTH, my_file);
        }
        fclose(my_file);
    }

    // >=1 instance per MPI Task, each gets the whole file, through a bcast
    else if (INSTANCE_PER_NP > 0 || NP_PER_INSTANCE <= 1) {
        //LP_COUNT == TOTAL_GATES == g_tw_nlp
        if (g_tw_mynode == 0) {
            MPI_File fh;
            MPI_Status req;
            
            MPI_File_open(MPI_COMM_SELF, fullpath, MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
            for (i = 0; i < g_tw_nlp; i++) {
                MPI_File_read_at(fh, i * (LINE_LENGTH - 1), global_input[i], LINE_LENGTH-1, MPI_CHAR, &req);
            }
            MPI_File_close(&fh);
        }
        
        //Simple Bcast, no packing
        for (i = 0; i < g_tw_nlp; i++) {
            int rc = MPI_Bcast(global_input[i], LINE_LENGTH, MPI_CHAR, 0, MPI_COMM_WORLD);
            if (rc != MPI_SUCCESS) {
                printf("BCast faild on %d\n", i);
            }
        }
    }
    
    //MPI_READ on rank 0, scatter around
    else {
        if (g_tw_mynode == 0) {

            FILE *f;
            f = fopen(fullpath, "r");
            char *block = (char *) malloc(MEM_SIZE);

            for (i = 0; i < g_tw_nnodes; i++) {
                fread(block, MEM_SIZE, 1, f);
                if (g_tw_mynode == i) {
                    memcpy(global_input, block, MEM_SIZE);
                } else {
                    MPI_Send(block, MEM_SIZE, MPI_CHAR, i, 0, MPI_COMM_WORLD);
                }
            }

            fclose();
            free(block);
        } else {
            MPI_Status req;
            MPI_Recv(global_input, MEM_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &req);
        }
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

