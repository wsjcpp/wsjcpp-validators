cmake_minimum_required(VERSION 3.0)

project(wsjcpp-validators C CXX)

find_package(Threads REQUIRED)

include(${CMAKE_CURRENT_SOURCE_DIR}/src.wsjcpp/CMakeLists.txt)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${wsjcpp-validators_SOURCE_DIR})

# Sources

# include header dirs
list (APPEND WSJCPP_INCLUDE_DIRS "src")

list (APPEND WSJCPP_SOURCES "src/wsjcpp_validators.h")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_validators.cpp")
list (APPEND WSJCPP_SOURCES "src/main.cpp")

include_directories(${WSJCPP_INCLUDE_DIRS})

add_executable ("wsjcpp-validators" ${WSJCPP_SOURCES})

target_link_libraries("wsjcpp-validators" ${CMAKE_THREAD_LIBS_INIT} )

install(
    TARGETS
        "wsjcpp-validators"
    RUNTIME DESTINATION
        /usr/bin
)
