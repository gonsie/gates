#define VERIFY_MAPPING 1

tw_peid gates_custom_round_robin_mapping_to_pe(tw_lpid gid){
    assert(gid >= 0);
    assert(gid < TOTAL_GATE_COUNT);
    return (tw_peid) gid % GLOBAL_NP_COUNT;
}

void gates_custom_round_robin_mapping_setup(void){
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

tw_lp * gates_custom_round_robin_mapping_to_local(tw_lpid gid){
    int id = 0;
    int ins_gid = gid % TOTAL_GATE_COUNT;
    id = ins_gid / GLOBAL_NP_COUNT;
    assert(id < LP_COUNT + 1);
    assert(id >= 0);

    return g_tw_lp[id];
}
/*
tw_peid gates_custom_many_copies_round_robin_mapping_to_pe(tw_lpid gid){
    assert(gid >= 0);
    assert(gid < COPY_COUNT * TOTAL_GATE_COUNT);
    if (NP_PER_INSTANCE > 0) {
        return (tw_peid) (NP_PER_INSTANCE * instance_id(gid)) + instance_node(gid);
    }
    return node_instance(gid);
}

void gates_custom_many_copies_round_robin_mapping_setup(void){
    tw_pe *pe;
    int kpid;
    int lpgid, lplid;
    int j;

    //Minimum lps per kp, and how many kps have 1 extra lp
    int lps_per_kp = g_tw_nlp / g_tw_nkp;
    int extra_kps = g_tw_nlp - (lps_per_kp * g_tw_nkp);

    //The gid of my g_tw_lp[0], round robin stride
    int stride;
    if (NP_PER_INSTANCE > 0) {
        g_tw_lp_offset = ((g_tw_mynode / NP_PER_INSTANCE) * TOTAL_GATE_COUNT) + (g_tw_mynode % NP_PER_INSTANCE);
        stride = NP_PER_INSTANCE;
    } else {
        g_tw_lp_offset = g_tw_mynode * INSTANCE_PER_NP * TOTAL_GATE_COUNT;
        stride = 1;
    }

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

tw_lp * gates_custom_many_copies_round_robin_mapping_to_local(tw_lpid gid){
    int id = 0;
    if (NP_PER_INSTANCE > 0) {
        int ins_gid = gid % TOTAL_GATE_COUNT;
        id = ins_gid / NP_PER_INSTANCE;
        assert(id < LP_COUNT + 1);
    } else {
        id = gid - (node_instance(gid) * INSTANCE_PER_NP * TOTAL_GATE_COUNT);
        assert(id < INSTANCE_PER_NP * TOTAL_GATE_COUNT);
    }
    assert(id >= 0);

    return g_tw_lp[id];
}

int instance_id(unsigned int gid) {
    return gid / TOTAL_GATE_COUNT;
}

int instance_node(unsigned int gid) {
    if (NP_PER_INSTANCE > 0) {
        // round robin mapping among processors
        return  (gid % TOTAL_GATE_COUNT) % NP_PER_INSTANCE;
    }
    return 0;
}

int node_instance(unsigned int gid) {
    if (INSTANCE_PER_NP > 0) {
        return instance_id(gid) / INSTANCE_PER_NP;
    }
    return 0;
}

int instance_x(unsigned int gid) {
    return instance_id(gid) % X_COUNT;
}

int instance_y(unsigned int gid) {
    return instance_id(gid) / X_COUNT;
}

int instance_0(unsigned int gid) {
    return instance_id(gid) * TOTAL_GATE_COUNT;
}
*/
/*
tw_peid gates_custom_linear_mapping_to_pe(tw_lpid gid){
    if (gid >= EXTRA_LP_COUNT * (LP_COUNT + 1)) {
        return (tw_peid) ((gid - EXTRA_LP_COUNT) / LP_COUNT);
    } else {
        return (tw_peid) gid / (LP_COUNT + 1);
    }
}

void gates_custom_linear_mapping_setup(void){
    tw_pe *pe;
    int nlp_per_kp;
    int lpid, kpid;
    int i, j;

    nlp_per_kp = ceil((double) g_tw_nlp / (double) g_tw_nkp);
    if(!nlp_per_kp) tw_error(TW_LOC, "Not enough KPs defined: %d", g_tw_nkp);

    g_tw_lp_offset = (g_tw_mynode * LP_COUNT) + min(g_tw_mynode, EXTRA_LP_COUNT);

#if VERIFY_MAPPING
    printf("Node %d: nlp %lld, offset %lld\n", g_tw_mynode, g_tw_nlp, g_tw_lp_offset);
#endif

    for (kpid = 0, lpid = 0, pe = NULL; (pe = tw_pe_next(pe)); ) {

        for (i = 0; i < nkp_per_pe; i++, kpid++) {
            tw_kp_onpe(kpid, pe);

            for (j = 0; j < nlp_per_kp && lpid < g_tw_nlp; j++, lpid++) {
                tw_lp_onpe(lpid, pe, g_tw_lp_offset + lpid);
                tw_lp_onkp(g_tw_lp[lpid], g_tw_kp[kpid]);
#if VERIFY_MAPPING
                if (0 == j % 20000) {
                    printf("Node %d\tPE %d\tKP %d\t%d\n", g_tw_mynode, pe->id, kpid, lpid + g_tw_lp_offset);
                }
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

tw_lp * gates_custom_linear_mapping_to_local(tw_lpid lpid){
    assert(lpid >= 0);
    assert(lpid < LP_COUNT * tw_nnodes() + EXTRA_LP_COUNT);

    int id = lpid - g_tw_lp_offset;

    return g_tw_lp[id];
}
*/
