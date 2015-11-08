#include "generic-model.h"
#include "routing.h"

#define VERIFY_MAPPING 1

tw_peid gates_custom_mapping_to_pe(tw_lpid gid){
    assert(gid >= 0);
    assert(gid < routing_table_lp[RO_TOTAL]);
    return 0;
}

void gates_custom_mapping_setup(void){
    tw_pe *pe;
    int kpid;
    int lpgid, lplid;
    int j;

    //Minimum lps per kp, and how many kps have 1 extra lp
    int lps_per_kp = g_tw_nlp / g_tw_nkp;
    int extra_kps = g_tw_nlp - (lps_per_kp * g_tw_nkp);

    //The gid of my g_tw_lp[0], round robin stride
    int stride;
    g_tw_lp_offset = ((g_tw_mynode / GLOBAL_NP_COUNT) * TOTAL_GATE_COUNT) + (g_tw_mynode % GLOBAL_NP_COUNT);
    stride = GLOBAL_NP_COUNT;

#if VERIFY_MAPPING
    printf("Node %d: nlp %d, offset %d, lps_per_kp %d, extra_kps %d\n", g_tw_mynode, g_tw_nlp, g_tw_lp_offset, lps_per_kp, extra_kps);
#endif

    //This loop happens once on each pe
    //set starting local and global ids for the LPs on this node
    for (lplid = 0, lpgid = g_tw_lp_offset, pe = NULL; (pe = tw_pe_next(pe)); ) {

        //For each kp
        for (kpid = 0; kpid < g_tw_nkp; kpid++) {

            tw_kp_onpe(kpid, pe);

            //lps on this particular kp
            int nlps = lps_per_kp;
            if (kpid < extra_kps) {
                nlps++;
            }

            for (j = 0; j < nlps; j++, lpgid += stride, lplid++) {
                tw_lp_onpe(lplid, pe, lpgid);
                tw_lp_onkp(g_tw_lp[lplid], g_tw_kp[kpid]);

#if VERIFY_MAPPING
                if (0 == j) {
                    printf("PE %d\tKP %d\tLP %d\n", pe->id, kpid, lpgid);
                }
#endif
            }
        }
    }
}

tw_lp * gates_custom_mapping_to_local(tw_lpid gid){
    int id = 0;
    int ins_gid = gid % TOTAL_GATE_COUNT;
    id = ins_gid / GLOBAL_NP_COUNT;
    assert(id < LP_COUNT + 1);
    assert(id >= 0);

    return g_tw_lp[id];
}
