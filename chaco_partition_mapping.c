// ASSUME NO COPIES

#include <assert.h>
#include "chaco_partition.h"

//#define VERIFY_MAPPING 1

tw_peid gates_chaco_partition_mapping_to_pe(tw_lpid gid){
    assert(gid >= 0);
    assert(gid < TOTAL_GATE_COUNT);
    int i;
    int sum = 0;
    for (i = 0; i < GLOBAL_NP_COUNT; i++) {
        sum += partition_lengths[i];
        if (gid < sum) {
            return i;
        }
    }
    // FREAK OUT
    return -1;
}

// A LINEAR MAPPING WITH UNEVEN LENGTHS
void gates_chaco_partition_mapping_setup(void){
    tw_pe *pe;
    int kpid;
    int lpgid, lplid;
    int i;

    //Minimum lps per kp, and how many kps have 1 extra lp
    int lps_per_kp = g_tw_nlp / g_tw_nkp;
    int extra_kps = g_tw_nlp - (lps_per_kp * g_tw_nkp);

    g_tw_lp_offset = 0;
    for (i = 0; i < g_tw_mynode; i++) {
        g_tw_lp_offset += partition_lengths[i];
    }
    
#if VERIFY_MAPPING
    printf("Node %d: nlp %lld, offset %lld, lps_per_kp %d, extra_kps %d\n", g_tw_mynode, g_tw_nlp, g_tw_lp_offset, lps_per_kp, extra_kps);
#endif
    
    //This loop happens once on each pe
    //set starting local and global ids for the LPs on this node
    for (lplid = 0, lpgid = g_tw_lp_offset, pe = NULL; (pe = tw_pe_next(pe)); ) {

        //For each kp
        for (kpid = 0; kpid < g_tw_nkp; kpid++) {
            tw_kp_onpe(kpid, pe);

            int nlps = lps_per_kp;
            if (kpid < extra_kps) {
                nlps++;
            }

            //lps on this particular kp
            for (i = 0; i < nlps; i++, lpgid++, lplid++) {
                tw_lp_onpe(lplid, pe, lpgid);
                tw_lp_onkp(g_tw_lp[lplid], g_tw_kp[kpid]);

#if VERIFY_MAPPING
                if(0) printf("PE %d\tKP %d\tLP %d\n", pe->id, kpid, lpgid);
#endif
            }
        }
    }
        
    if (!g_tw_lp[g_tw_nlp - 1]) {
        tw_error(TW_LOC, "Not all LPs defined! (g_tw_nlp=%d)", g_tw_nlp);
    }
    
    if (g_tw_lp[g_tw_nlp - 1]->gid != g_tw_lp_offset + g_tw_nlp - 1) {
        tw_error(TW_LOC, "LPs not sequentially enumerated!");
    }
}

tw_lp * gates_chaco_partition_mapping_to_local(tw_lpid lpid){
    assert(lpid >= 0);
    assert(lpid < TOTAL_GATE_COUNT);
    
    int id = lpid - g_tw_lp_offset;
    return g_tw_lp[id];
}
