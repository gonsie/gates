INCLUDE_DIRECTORIES(${ROSS_SOURCE_DIR})

# configure the run for the specified number of processors
IF(NOT np)
       SET(_np 1 CACHE INTERNAL "sequential" FORCE)
ELSE(NOT np)
	SET(_np ${np} CACHE INTERNAL "parallel number of processors" FORCE)	
ENDIF(NOT np)
UNSET(np CACHE)

# copy the data file to the build directory
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/ccx_mpi.bench ${CMAKE_CURRENT_BINARY_DIR}/ccx_mpi.bench COPYONLY)

# calculate variables for run_config.h
CMAKE_POLICY(SET CMP0007 OLD)
EXECUTE_PROCESS(COMMAND wc -l ${CMAKE_CURRENT_SOURCE_DIR}/ccx_mpi.bench
   OUTPUT_VARIABLE _output OUTPUT_STRIP_TRAILING_WHITESPACE)
STRING(REPLACE " " ";" _outlist ${_output})
LIST(GET _outlist 0 _ngates)

MATH(EXPR _ng "${_ngates} + 2")
MATH(EXPR _nlp "${_ng}/${_np}")
MATH(EXPR _xlp "${_ng} - (${_nlp} * ${_np})")

EXECUTE_PROCESS(COMMAND head -n 1 ${CMAKE_CURRENT_SOURCE_DIR}/ccx_mpi.bench COMMAND wc -c
	OUTPUT_VARIABLE _linelen OUTPUT_STRIP_TRAILING_WHITESPACE)
MATH(EXPR _ll  "${_linelen} + 1")

#MESSAGE("configure_file ${_ngates} ${_np} ${_nlp} ${_xlp} ${_ll}")

# write the header with variables
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/run_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/run_config.h)

SET(gates_srcs
	gates_driver.c 
	gate.h
	ptwHeader.h
)

SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_SOURCE_DIR}/run_config.h 
	PROPERTIES GENERATED true)
 
ADD_EXECUTABLE(gates ${gates_srcs} ${CMAKE_CURRENT_SOURCE_DIR}/run_config.h)

TARGET_LINK_LIBRARIES(gates ROSS m)
