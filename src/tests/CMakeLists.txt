file(GLOB ALL_TESTS
  "test_*.cpp"
)

list (APPEND TEST_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../")
list (APPEND TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../src.wsjcpp/wsjcpp_core/wsjcpp_core.cpp")
list (APPEND TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../wsjcpp_validators/wsjcpp_validators.cpp")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY tests)

foreach(_TEST ${ALL_TESTS})
  get_filename_component(TEST_NAME ${_TEST} NAME_WE)
  add_executable(${TEST_NAME}
    ${_TEST}
    ${TEST_SOURCES}
  )
  target_link_libraries(${TEST_NAME} -lpthread ${WSJCPP_LIBRARIES})

  add_test(
    NAME ${TEST_NAME}
    COMMAND $<TARGET_FILE:${TEST_NAME}>
  )
  message(${CMAKE_CURRENT_BINARY_DIR}/tests)
  set_target_properties (${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY tests)
endforeach()
