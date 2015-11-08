INCLUDE_DIRECTORIES(${ROSS_SOURCE_DIR} ${ROSS_BINARY_DIR})
INCLUDE_DIRECTORIES(${RIO_SOURCE_DIR} ${RIO_BINARY_DIR})

## DATA FILES
# configure the run for the specified number of modules
IF(NOT np)
       SET(_np 237 CACHE INTERNAL "OpenSPARC T2 CPU" FORCE)
ELSE(NOT np)
    SET(_np ${np} CACHE INTERNAL "Other Project" FORCE)
ENDIF(NOT np)
UNSET(np CACHE)

FOREACH(_i RANGE ${_np})
    # copy the data file to the build directory
    SET(_block_data_file ${CMAKE_CURRENT_SOURCE_DIR}/datafile-${_i}.lnk)
    CONFIGURE_FILE(${_block_data_file} ${CMAKE_CURRENT_BINARY_DIR}/data-${_i}.vbench COPYONLY)
ENDFOREACH(_i)

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
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/run_config.h.in ${CMAKE_CURRENT_BINARY_DIR}/run_config.h @ONLY)

SET(gates_srcs
    gates_main.c
    gates_driver.c
    gates_model.h
    library.h
    library.c
)

SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_SOURCE_DIR}/run_config.h.in PROPERTIES GENERATED false)
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/run_config.h PROPERTIES GENERATED true)

ADD_EXECUTABLE(gates ${gates_srcs} ${CMAKE_CURRENT_BINARY_DIR}/run_config.h)

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
