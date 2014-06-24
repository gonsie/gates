INCLUDE_DIRECTORIES(${ROSS_SOURCE_DIR})

## NP

# configure the run for the specified number of processors
IF(NOT np)
       SET(_np 1 CACHE INTERNAL "sequential" FORCE)
ELSE(NOT np)
	SET(_np ${np} CACHE INTERNAL "parallel number of processors" FORCE)	
ENDIF(NOT np)
UNSET(np CACHE)

## DATA FILE

# copy the data file to the build directory
# EXECUTE_PROCESS(COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/scripts/reorder.py ${CMAKE_CURRENT_SOURCE_DIR}/data_file.lnk ${_np}
#     OUTPUT_VARIABLE _block_data_file OUTPUT_STRIP_TRAILING_WHITESPACE)
SET(_block_data_file ${CMAKE_CURRENT_SOURCE_DIR}/better_partition_ccx_lsi.txt.renumbered.pad.std)
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
SET(_ngates 200981)
SET(_maxlp 7672)

EXECUTE_PROCESS(COMMAND head -n 1 ${CMAKE_CURRENT_BINARY_DIR}/data.vbench COMMAND wc -c
	OUTPUT_VARIABLE _linelen OUTPUT_STRIP_TRAILING_WHITESPACE)
MATH(EXPR _ll  "${_linelen}")

SET(_grep_str "^\\S* 163 ")
EXECUTE_PROCESS(COMMAND grep -m 1 ${_grep_str} ${CMAKE_CURRENT_SOURCE_DIR}/data_file.lnk
    OUTPUT_VARIABLE _output OUTPUT_STRIP_TRAILING_WHITESPACE)
STRING(REPLACE " " ";" _outlist ${_output})
LIST(GET _outlist 0 _fanout)

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
MATH(EXPR _nlp "${_ng}/${_np}")
MATH(EXPR _xlp "${_ng} - (${_nlp} * ${_np})")

# write the header with variables
MESSAGE("configure_file\n\tngates = ${_ngates}\n\tline length = ${_ll}\n\tfanout = ${_fanout}\n\tnp = ${_np}\n\tnlp =  ${_nlp}\n\txlp = ${_xlp}")
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/run_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/run_config.h)

SET(gates_srcs
    gates_main.c
    gates_driver.c 
    gates_model.h
    library.h
    library.c
    chaco_partition.h
    chaco_partition_mapping.c
    chaco_32.c
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
