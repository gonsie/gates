INCLUDE_DIRECTORIES(${ROSS_SOURCE_DIR})

SET(gates_srcs
	gates_driver.c  
	gate.h
	ptwHeader.h
)

ADD_EXECUTABLE(gates ${gates_srcs})

TARGET_LINK_LIBRARIES(gates ROSS m)
