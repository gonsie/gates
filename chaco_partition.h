
#include "ross.h"
#include "run_config.h"
#include "gates_model.h"

extern int partition_lengths[];

// based on Chaco mapping
void gates_chaco_partition_mapping_setup(void);
tw_lp * gates_chaco_partition_mapping_to_local(tw_lpid lpid);
tw_peid gates_chaco_partition_mapping_to_pe(tw_lpid gid);
