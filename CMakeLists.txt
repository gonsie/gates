INCLUDE_DIRECTORIES(${ROSS_SOURCE_DIR})

## NP

# configure the run for the specified number of processors
IF(NOT np)
       SET(_np 1 CACHE INTERNAL "sequential" FORCE)
ELSE(NOT np)
	SET(_np ${np} CACHE INTERNAL "parallel number of processors" FORCE)	
ENDIF(NOT np)
UNSET(np CACHE)

## SYNTHETIC GRID CONFIGURATION

# configure the run for the specified replication (grid based)
# x
IF(NOT z)
       SET(_x 1 CACHE INTERNAL "single width" FORCE)
ELSE(NOT z)
	SET(_x ${z} CACHE INTERNAL "multiple width with linking" FORCE)	
ENDIF(NOT z)
UNSET(z CACHE)

# y --> use old policy to avoid "True / Yes / y"
CMAKE_POLICY(SET CMP0012 OLD)
IF(NOT y)
    SET(_y 1 CACHE INTERNAL "single height" FORCE)
ELSE(NOT y)
    SET(_y ${y} CACHE INTERNAL "multiple height no linking" FORCE)	
ENDIF(NOT y)
UNSET(y CACHE)

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

## DATA FILE

# copy the data file to the build directory
EXECUTE_PROCESS(COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/scripts/reorder.py ${CMAKE_CURRENT_SOURCE_DIR}/data_file.lnk ${_np}
    OUTPUT_VARIABLE _block_data_file OUTPUT_STRIP_TRAILING_WHITESPACE)
MESSAGE("${_block_data_file}")
CONFIGURE_FILE(${_block_data_file} ${CMAKE_CURRENT_BINARY_DIR}/data.vbench COPYONLY)
#CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/gid_data/gid_ccx_data_np${_enp}.vbench ${CMAKE_CURRENT_BINARY_DIR}/data.vbench COPYONLY)
#CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/gid_ccx_data.vbench ${CMAKE_CURRENT_BINARY_DIR}/data.vbench COPYONLY)

# calculate single instance size
CMAKE_POLICY(SET CMP0007 OLD)
EXECUTE_PROCESS(COMMAND wc -l ${CMAKE_CURRENT_BINARY_DIR}/data.vbench
    OUTPUT_VARIABLE _output OUTPUT_STRIP_TRAILING_WHITESPACE)
STRING(REPLACE " " ";" _outlist ${_output})
LIST(GET _outlist 0 _ngates)

EXECUTE_PROCESS(COMMAND head -n 1 ${CMAKE_CURRENT_BINARY_DIR}/data.vbench COMMAND wc -c
	OUTPUT_VARIABLE _linelen OUTPUT_STRIP_TRAILING_WHITESPACE)
MATH(EXPR _ll  "${_linelen}")

## WAVE FILES

# if specified, copy the wave data file to build directory
IF(NOT wave)
    SET(_wc 0 CACHE INTERNAL "no waves" FORCE)
ELSE(NOT wave)
    SET(_wc ${wave} CACHE INTERNAL "wave viewer" FORCE)
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/wave_data/wave_form${wave}.txt ${CMAKE_CURRENT_BINARY_DIR}/wave.txt COPYONLY)
ENDIF(NOT wave)
UNSET(wave CACHE)

## RUN_CONFIG.H

# calculate single instance run variables
MATH(EXPR _ng "${_ngates}")
MATH(EXPR _nlp "${_ng}/${_enp}")
MATH(EXPR _xlp "${_ng} - (${_nlp} * ${_enp})")

# write the header with variables
MESSAGE("configure_file\n\tngates = ${_ngates}\n\tline length = ${_ll}\n\tnp = ${_np}\n\tx = ${_x}\n\ty = ${_y}\n\tx*y =  ${_xy}\n\tinp = ${_inp}\n\tinp = ${_npi}\n\tnlp =  ${_nlp}\n\txlp = ${_xlp}")
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/run_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/run_config.h)

SET(gates_srcs
    gates_main.c
    gates_driver.c 
    gates_model.h
    library_types.h
    library_functions.c
    library_lookups.c
)

SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_SOURCE_DIR}/run_config.h.in
	PROPERTIES GENERATED false)

SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_SOURCE_DIR}/run_config.h 
	PROPERTIES GENERATED true)
 
ADD_EXECUTABLE(gates ${gates_srcs} ${CMAKE_CURRENT_SOURCE_DIR}/run_config.h)

TARGET_LINK_LIBRARIES(gates ROSS m)

IF(UNIT_TESTS)
        SET(TEST_DIR $(ROSS_SOURCE_DIR)/../test)
        INCLUDE_DIRECTORIES($(TEST_DIR))

        # Generate test_Runner.c from test file
        ADD_CUSTOM_COMMAND(
                OUTPUT $(CMAKE_CURRENT_SOURCE_DIR)/gates_test_Runner.c
                COMMAND /usr/bin/ruby $(CMAKE_SOURCE_DIR)/test/auto/generate_test_runner.rb $(CMAKE_CURRENT_SOURCE_DIR)/gates_test.c
                DEPENDS $(CMAKE_CURRENT_SOURCE_DIR)/gates_test.c
        )
        ADD_EXECUTABLE(gates-test $(TEST_DIR)/unity.c gates_test.c gates_test_Runner.c $(gates_srcs))

        TARGET_LINK_LIBRARIES(gates-test ROSS m)
        GET_TARGET_PROPERTY(test_binary gates-test LOCATION)

        # Make sure you run the test executable after building the binary
        ADD_CUSTOM_TARGET(tester ALL DEPENDS gates-test)
        ADD_CUSTOM_COMMAND(
                TARGET tester
                COMMAND $(test_binary)
                DEPENDS gates-test
        )
ENDIF(UNIT_TESTS)
