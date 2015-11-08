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

## Print GATES Hash
LIST(APPEND CMAKE_MODULE_PATH "${ROSS_SOURCE_DIR}/cmake/")
INCLUDE(GetGitRevisionDescription)
GET_GIT_HEAD_REVISION(GIT_RESPEC_G GIT_SHA1_G)

## RUN-CONFIG.H
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/gates-config.h.in ${CMAKE_CURRENT_BINARY_DIR}/gates-config.h @ONLY)
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_SOURCE_DIR}/gates-config.h.in PROPERTIES GENERATED FALSE)
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/gates-config.h PROPERTIES GENERATED TRUE)


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
