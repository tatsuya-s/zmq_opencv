project (zmq-opencv)
cmake_minimum_required(VERSION 2.8)

find_package (OpenCV REQUIRED)

find_path(ZeroMQ_ROOT_DIR NAMES include/zmq.hpp)
find_library(ZeroMQ_LIBS NAMES zmq libzmq HINTS ${ZeroMQ_ROOT_DIR}/lib)
find_path(ZeroMQ_INCLUDE_DIR NAMES zmq.hpp HINTS ${ZeroMQ_ROOT_DIR}/include)

include_directories(${ZeroMQ_INCLUDE_DIR})
link_directories(${ZeroMQ_LIB_DIR})

add_executable(client src/client.cpp)
target_link_libraries(client ${ZeroMQ_LIBS} ${OpenCV_LIBS})

add_executable(server src/server.cpp)
target_link_libraries(server ${ZeroMQ_LIBS} ${OpenCV_LIBS})