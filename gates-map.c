#include <assert.h>
#include "generic-model.h"
#include "routing.h"

#define VERIFY_MAPPING 1

tw_peid gates_custom_mapping_to_pe(tw_lpid gid){
    assert(gid < routing_table_lp[RO_TOTAL+1]);
    int i;
    for (i = 0; i < tw_nnodes(); i++) {
        if (gid < (*routing_table_mpi)[i+1]) {
            return i;
        }
    }
    tw_error(TW_LOC, "ERROR: can't map gid %llu to a PE", gid);
}

void gates_custom_mapping_setup(void){
    tw_pe *pe;
    int kpid;
    int lpgid, lplid;
    int j;

    //PARTS MAPPING
    g_tw_nkp = g_tw_nlp / LPS_PER_KP;
    int extra_kps = g_tw_nlp - (g_tw_nkp * LPS_PER_KP);

#if VERIFY_MAPPING
    printf("Node %ld: nlp %llu, offset %llu, extra_kps %d\n", g_tw_mynode, g_tw_nlp, g_tw_lp_offset, extra_kps);
#endif

    //This loop happens once on each pe
    //set starting local and global ids for the LPs on this node
    for (lplid = 0, lpgid = g_tw_lp_offset, pe = NULL; (pe = tw_pe_next(pe)); ) {

        //For each kp
        for (kpid = 0; kpid < g_tw_nkp; kpid++) {

            tw_kp_onpe(kpid, pe);

            //lps on this particular kp
            int nlps = LPS_PER_KP;
            if (kpid < extra_kps) {
                nlps++;
            }

            for (j = 0; j < nlps; j++, lpgid++, lplid++) {
                tw_lp_onpe(lplid, pe, lpgid);
                tw_lp_onkp(g_tw_lp[lplid], g_tw_kp[kpid]);

#if VERIFY_MAPPING
                if (0 == j) {
                    printf("PE %lu\tKP %d\tLP %d\n", pe->id, kpid, lpgid);
                }
#endif
            }
        }
    }
}

tw_lp * gates_custom_mapping_to_local(tw_lpid gid){
    assert(gid < routing_table_lp[RO_TOTAL+1]);

    int id = gid - g_tw_lp_offset;
    assert(id >= (*routing_table_mpi)[g_tw_mynode]);
    assert(id < (*routing_table_mpi)[g_tw_mynode+1]);

    return g_tw_lp[id];
}
