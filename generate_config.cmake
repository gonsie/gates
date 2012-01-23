CMAKE_POLICY(SET CMP0007 OLD)

GET_PROPERTY(_test1 GLOBAL PROPERTY COMPILE_DEFINITIONS)
#GET_PROPERTY(_test3 TARGET gates PROPERTY COMPILED_DEFINITIONS)
GET_PROPERTY(_test4 SOURCE gates_driver.c PROPERTY COMPILED_DEFINITIONS)
MESSAGE("TESTING1234: ${_test1} ${_test2} ${_test3} ${_test4}")

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

EXECUTE_PROCESS(COMMAND head -n 1 ccx_mpi.bench COMMAND wc -c
	OUTPUT_VARIABLE _linelen OUTPUT_STRIP_TRAILING_WHITESPACE)
MATH(EXPR _ll  "${_linelen} + 1")
MESSAGE("line len is ${_ll}")

SET(gate_source ${CMAKE_CURRENT_SOURCE_DIR}/../../../../rossnet/trunk/ross/models/gates)
file(WRITE ${gate_source}/run_config.h "#define TOTAL_GATE_COUNT ${_ngates}\n" )
file(APPEND ${gate_source}/run_config.h "#define NP_COUNT ${_np}\n")
file(APPEND ${gate_source}/run_config.h "#define LP_COUNT ${_nlp}\n")
file(APPEND ${gate_source}/run_config.h "#define LINE_LENGTH ${_ll}\n")
