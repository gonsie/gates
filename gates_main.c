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

//#define VERIFY_READ 1

const tw_optdef gates_opts[] = {
    TWOPT_GROUP("Gates Model"),
    TWOPT_UINT("source_interval", source_interval,"time between source sending waves of input"),
    TWOPT_UINT("sink_interval", sink_interval, "time between reporting of sink statistics"),
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
    
    if (WAVE_COUNT != 0 && g_tw_synchronization_protocol > 2) {
        printf("ERROR: Waveform viewing is not supported for non-conservative protocols.\n");
        return 1;
    }
    
    if (g_tw_mynode == 0) {
        printf("Gates Configuration:\n\t");
        printf("X_COUNT = %d * Y_COUNT = %d => COPY_COUNT = %d\n\t", X_COUNT, Y_COUNT, COPY_COUNT);
        printf("NP_PER_INSTANCE = %d --or-- INSTANCE_PER_NP = %d\n\t", NP_PER_INSTANCE, INSTANCE_PER_NP);
        printf("TOTAL_GATE_COUNT = %d, LP_COUNT = %d\n", TOTAL_GATE_COUNT, LP_COUNT);
        if (WAVE_COUNT) {
            printf("\tWAVE_VIEW Enabled: %d\n", WAVE_COUNT);
        }
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
    char dataname[100] = "/data.vbench";
    char *datapath = dirname(argv[0]);
    strcat(datapath, dataname);
    
    //single processor, single file
    if (g_tw_synchronization_protocol == 1) {
        //sequential
        FILE *my_file = fopen(datapath, "r");
        for (i = 0; i < LP_COUNT; i++) {
            fgets(global_input[i], LINE_LENGTH+2, my_file);
        }
        fclose(my_file);
    }

    // >=1 instance per MPI Task, each gets the whole file, through a bcast
    else if (INSTANCE_PER_NP > 0 || NP_PER_INSTANCE <= 1) {
        //LP_COUNT == TOTAL_GATES == g_tw_nlp
        if (g_tw_mynode == 0) {
            MPI_File fh;
            MPI_Status req;
            
            MPI_File_open(MPI_COMM_SELF, datapath, MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
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
    // BLOCK_SIZE is the size of the block of text for any single processor
    // the text has been grouped into blocks for each processor
    else {
        // size of text block to be read
        int BLOCK_SIZE = LP_COUNT * LINE_LENGTH;
        if (g_tw_mynode < EXTRA_LP_COUNT) {
            BLOCK_SIZE += LINE_LENGTH;
        }
        char *block = (char *) malloc(BLOCK_SIZE);

        // all reading happens from task 0
        if (g_tw_mynode == 0) {

            FILE *f;
            f = fopen(datapath, "r");
            int MEM_SIZE = BLOCK_SIZE;

            for (i = 0; i < tw_nnodes(); i++) {
                fread(block, MEM_SIZE, 1, f);
                if (g_tw_mynode == i) {
                    for (j = 0; j < LP_COUNT + (i < EXTRA_LP_COUNT ? 1 : 0); j++) {
                        strncpy(global_input[j], block + (j * LINE_LENGTH), LINE_LENGTH);
                    }
                } else {
                    MPI_Send(block, MEM_SIZE, MPI_CHAR, i, 0, MPI_COMM_WORLD);
                }
                if ((i+1) == EXTRA_LP_COUNT) {
                    MEM_SIZE -= LINE_LENGTH;
                }
            }

            fclose(f);
            free(block);
        } else {
            MPI_Status req;
            MPI_Recv(block, BLOCK_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &req);
            for (j = 0; j < LP_COUNT + (g_tw_mynode < EXTRA_LP_COUNT ? 1 : 0); j++) {
                strncpy(global_input[j], block + (j * LINE_LENGTH), LINE_LENGTH);
            }
        }
    }

#if VERIFY_READ
    if (g_tw_mynode == 0) {
        printf("Line 0: %s\n", global_input[0]);
        printf("Line 1: %s\n", global_input[1]);
        printf("Line 2: %s\n", global_input[2]);
        printf("Line 3: %s\n", global_input[3]);
        printf("Line 100: %s\n", global_input[100]);
        printf("Line Last: %s\n", global_input[LP_COUNT-1]);
    }
#endif
    
    // read the wave file gids
    if (WAVE_COUNT != 0 && g_tw_mynode == 0) {
        char wavename[100] = "/wave.txt";
        char *wavepath = dirname(argv[0]);
        strcat(wavepath, wavename);
    
        FILE *f;
        f = fopen(wavepath, "r");
        
        fseek(f, 0, SEEK_END);
        int w_size = ftell(f);
        fseek(f, 0, SEEK_SET);
        
        char *wave_file = (char *)malloc(w_size);
        fread(wave_file, w_size, 1, f);
        fclose(f);
        
        char * wid;
        char * w_ptr = wave_file;
        i = 0;
        while ((wid = strsep(&w_ptr, "\n")) != NULL) {
            wave_gids[i] = atoi(wid);
            i++;
        }
        
        free(wave_file);

        assert(i == WAVE_COUNT);

        // add output vcd file
        char outname[100] = "/waveout.vcd";
        char *outpath = dirname(argv[0]);
        strcat(outpath, outname);

        f = fopen(outpath, "a");

        for (i = 0; i < WAVE_COUNT; i++) {
            fprintf(f, "$var wire 1 %c %d $end\n", (char)(i+33), wave_gids[i]);
        }
        fprintf(f, "$upscope $end\n$enddefinitions $end\n");

        fclose(f);
    }

    if (WAVE_COUNT != 0) {
        char outname[100];
        sprintf(outname, "/waveout.%d.vcd", g_tw_mynode);
        char *outpath = dirname(argv[0]);
        strcat(outpath, outname);
        wave_out_file = fopen(outpath, "a");
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

