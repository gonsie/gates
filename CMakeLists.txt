INCLUDE_DIRECTORIES(${ROSS_SOURCE_DIR})

# configure the run for the specified number of processors
IF(NOT np)
       SET(_np 1 CACHE INTERNAL "sequential" FORCE)
ELSE(NOT np)
	SET(_np ${np} CACHE INTERNAL "parallel number of processors" FORCE)	
ENDIF(NOT np)
UNSET(np CACHE)

# configure the run for the specified replication (grid based)
# x
IF(NOT x)
       SET(_x 1 CACHE INTERNAL "single width" FORCE)
ELSE(NOT x)
	SET(_x ${x} CACHE INTERNAL "multiple width with linking" FORCE)	
ENDIF(NOT x)
UNSET(x CACHE)

# y --> use old policy to avoid "True / Yes / y"
CMAKE_POLICY(SET CMP0012 OLD)
IF(NOT y)
    SET(_y 1 CACHE INTERNAL "single height" FORCE)
ELSE(NOT y)
    SET(_y ${y} CACHE INTERNAL "multiple height no linking" FORCE)	
ENDIF(NOT y)
UNSET(y CACHE)

# calculate single instance size
CMAKE_POLICY(SET CMP0007 OLD)
EXECUTE_PROCESS(COMMAND wc -l ${CMAKE_CURRENT_SOURCE_DIR}/ccx_mpi.bench
    OUTPUT_VARIABLE _output OUTPUT_STRIP_TRAILING_WHITESPACE)
STRING(REPLACE " " ";" _outlist ${_output})
LIST(GET _outlist 0 _ngates)

# calculate duplication run variables
MATH(EXPR _xy "${_x} * ${_y}")
IF(${_np} LESS ${_xy})
# many instances on a single processor
    MATH(EXPR _inp "${_xy} / ${_np}")
    SET(_npi 0)
    SET(_enp 1)
ELSE(${_np} LESS ${_xy})
# many processors for a single instance
    MATH(EXPR _npi "${_np} / ${_xy}") # assume _xy evenly divides _np and _xy > 0
    SET(_inp 0)
    SET(_enp ${_npi})
ENDIF(${_np} LESS ${_xy})

# calculate single instance run variables
MATH(EXPR _ng "${_ngates}")
MATH(EXPR _nlp "${_ng}/${_enp}")
MATH(EXPR _xlp "${_ng} - (${_nlp} * ${_enp})")

# copy the data file to the build directory
#CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/data/ccx_data_np${_enp}.vbench ${CMAKE_CURRENT_BINARY_DIR}/data.vbench COPYONLY)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/gid_ccx_data.vbench ${CMAKE_CURRENT_BINARY_DIR}/data.vbench COPYONLY)

EXECUTE_PROCESS(COMMAND head -n 1 ${CMAKE_CURRENT_SOURCE_DIR}/data/ccx_data_np1.vbench COMMAND wc -c
	OUTPUT_VARIABLE _linelen OUTPUT_STRIP_TRAILING_WHITESPACE)
MATH(EXPR _ll  "${_linelen} + 1")

#MESSAGE("configure_file ${_ngates} ${_ll} ${_np} ${_x} ${_y} ${_xy} ${_inp} ${_npi} ${_nlp} ${_xlp}")

# write the header with variables
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/run_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/run_config.h)

SET(gates_srcs
    gates_main.c
    gates_driver.c 
    gates_model.h
    gate.c
    gate.h
)

SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_SOURCE_DIR}/run_config.h.in
	PROPERTIES GENERATED false)

SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_SOURCE_DIR}/run_config.h 
	PROPERTIES GENERATED true)
 
ADD_EXECUTABLE(gates ${gates_srcs} ${CMAKE_CURRENT_SOURCE_DIR}/run_config.h)

TARGET_LINK_LIBRARIES(gates ROSS m)

SET(test_srcs
    gates_driver.c
    gates_test.cpp
    gates_model.h
    gate.c
    gate.h
)

#ADD_EXECUTABLE(test_gates ${test_srcs} ${CMAKE_CURRENT_SOURCE_DIR}/run_config.h)

#TARGET_LINK_LIBRARIES(test_gates ROSS m)    
