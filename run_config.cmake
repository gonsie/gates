EXECUTE_PROCESS(COMMAND grep _np ${CMAKE_SOURCE_DIR}/../../../CMakeCache.txt
	OUTPUT_VARIABLE temp_np OUTPUT_STRIP_TRAILING_WHITESPACE)
STRING(REPLACE "=" ";" temp_list ${temp_np})
LIST(GET temp_list 1 _np)
MESSAGE("did grep work? ${_np}")

EXECUTE_PROCESS(COMMAND wc -l ccx_mpi.bench
   OUTPUT_VARIABLE _output OUTPUT_STRIP_TRAILING_WHITESPACE)
STRING(REPLACE " " ";" _outlist ${_output})
LIST(GET _outlist 0 _ngates)

MATH(EXPR _ng "${_ngates} + 2")
EXECUTE_PROCESS(COMMAND python -c "from math import ceil; print int(ceil(${_ng}/float(${_np})))"
    OUTPUT_VARIABLE _nlp OUTPUT_STRIP_TRAILING_WHITESPACE)

SET(gate_source ${CMAKE_CURRENT_SOURCE_DIR}/../../../../rossnet/trunk/ross/models/gates)
file(WRITE ${gate_source}/run_config.h "#define TOTAL_GATE_COUNT ${_ngates}\n" )
file(APPEND ${gate_source}/run_config.h "#define NP_COUNT ${_np}\n")
file(APPEND ${gate_source}/run_config.h "#define LP_COUNT ${_nlp}\n")
