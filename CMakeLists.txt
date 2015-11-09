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
    SET(_block_data_file ${CMAKE_CURRENT_SOURCE_DIR}/data/data-${_i}.vbench)
    CONFIGURE_FILE(${_block_data_file} ${CMAKE_CURRENT_BINARY_DIR}/data/data-${_i}.vbench COPYONLY)
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
    gates-config.h
    generic-model.h
    library.h
    library.c
    routing.h
    routing.c
    gates-map.c
    gates-rio.c
    gates-driver.c
    gates.c
)
ADD_EXECUTABLE(gates ${gates_srcs})
TARGET_LINK_LIBRARIES(gates ROSS RIO m)

SET(module_loader_srcs
    generic-model.h
    library.h
    library.c
    routing.h
    routing.c
    gates-rio.c
    module-loader.c
)
ADD_EXECUTABLE(module_loader ${module_loader_srcs})
TARGET_LINK_LIBRARIES(module_loader ROSS RIO m)
