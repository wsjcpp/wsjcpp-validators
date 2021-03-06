# Automaticly generated by wsjcpp@v0.1.5
cmake_minimum_required(VERSION 3.0)

project(unit-tests C CXX)
add_definitions(-DWSJCPP_APP_VERSION="ut-v0.1.2")
add_definitions(-DWSJCPP_APP_NAME="unit-tests-wsjcpp-validators")

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
endif()

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${unit-tests_SOURCE_DIR})

set (WSJCPP_LIBRARIES "")
set (WSJCPP_INCLUDE_DIRS "")
set (WSJCPP_SOURCES "")

find_package(Threads REQUIRED)
list (APPEND WSJCPP_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

# wsjcpp-core:v0.1.7
list (APPEND WSJCPP_INCLUDE_DIRS "../src.wsjcpp/wsjcpp_core/")
list (APPEND WSJCPP_SOURCES "../src.wsjcpp/wsjcpp_core/wsjcpp_core.cpp")
list (APPEND WSJCPP_SOURCES "../src.wsjcpp/wsjcpp_core/wsjcpp_core.h")
list (APPEND WSJCPP_SOURCES "../src.wsjcpp/wsjcpp_core/wsjcpp_unit_tests.cpp")
list (APPEND WSJCPP_SOURCES "../src.wsjcpp/wsjcpp_core/wsjcpp_unit_tests.h")
list (APPEND WSJCPP_SOURCES "../src.wsjcpp/wsjcpp_core/wsjcpp_unit_tests_main.cpp")
list (APPEND WSJCPP_SOURCES "../src.wsjcpp/wsjcpp_core/wsjcpp_resources_manager.h")
list (APPEND WSJCPP_SOURCES "../src.wsjcpp/wsjcpp_core/wsjcpp_resources_manager.cpp")

# nlohmann/json:v3.9.1
list (APPEND WSJCPP_INCLUDE_DIRS "../src.wsjcpp/nlohmann_json/")
list (APPEND WSJCPP_SOURCES "../src.wsjcpp/nlohmann_json/json.hpp")

# wsjcpp-validators:v0.1.2
list (APPEND WSJCPP_INCLUDE_DIRS "../src")
list (APPEND WSJCPP_SOURCES "../src/wsjcpp_validators.h")
list (APPEND WSJCPP_SOURCES "../src/wsjcpp_validators.cpp")

# unit-tests
list (APPEND WSJCPP_INCLUDE_DIRS "src")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_email.h")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_email.cpp")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_uuid.h")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_uuid.cpp")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_string_list.h")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_string_list.cpp")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_jwt.h")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_jwt.cpp")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_date.h")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_date.cpp")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_time_h24.h")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_time_h24.cpp")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_date_time.h")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_date_time.cpp")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_reg_exp.h")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_reg_exp.cpp")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_base64.h")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_base64.cpp")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_url.h")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_url.cpp")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_number.h")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_number.cpp")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_hex.h")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_hex.cpp")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_string_length.h")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_string_length.cpp")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_is_valid_ip_v4.h")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_is_valid_ip_v4.cpp")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_is_valid_ip_v6.h")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_is_valid_ip_v6.cpp")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_integer_min_value.h")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_integer_min_value.cpp")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_integer_max_value.h")
list (APPEND WSJCPP_SOURCES "../unit-tests.wsjcpp/src/unit_test_validator_integer_max_value.cpp")

# required-libraries
list (APPEND WSJCPP_LIBRARIES "-lpthread")

include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.user-custom.txt)


include_directories(${WSJCPP_INCLUDE_DIRS})

add_executable ("unit-tests" ${WSJCPP_SOURCES})

target_link_libraries("unit-tests" -lpthread ${WSJCPP_LIBRARIES} )

install(
    TARGETS
        "unit-tests"
    RUNTIME DESTINATION
        /usr/bin
)


