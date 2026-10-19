cmake_minimum_required(VERSION 3.16)
project(SuperJupiterTimeAggregate VERSION 0.1.1 LANGUAGES CXX)

set(_superjupiter_time_aggregate_top_level OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(_superjupiter_time_aggregate_top_level ON)
endif()
option(SUPERJUPITER_TIME_AGGREGATE_BUILD_TESTS "Build TimeAggregate tests" ${_superjupiter_time_aggregate_top_level})
option(SUPERJUPITER_TIME_AGGREGATE_BUILD_EXAMPLES "Build TimeAggregate host example" ${_superjupiter_time_aggregate_top_level})
option(SUPERJUPITER_TIME_AGGREGATE_INSTALL "Generate TimeAggregate install rules" ${_superjupiter_time_aggregate_top_level})

add_library(SuperJupiterTimeAggregate INTERFACE)
add_library(SuperJupiter::TimeAggregate ALIAS SuperJupiterTimeAggregate)
set_target_properties(SuperJupiterTimeAggregate PROPERTIES EXPORT_NAME TimeAggregate)
target_include_directories(SuperJupiterTimeAggregate INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include>)
target_compile_features(SuperJupiterTimeAggregate INTERFACE cxx_std_11)

if(SUPERJUPITER_TIME_AGGREGATE_BUILD_TESTS)
  enable_testing()
  add_executable(superjupiter-time-aggregate-review tests/review_regressions.cpp)
  target_link_libraries(superjupiter-time-aggregate-review PRIVATE SuperJupiter::TimeAggregate)
  add_test(NAME superjupiter-time-aggregate-review COMMAND superjupiter-time-aggregate-review)
  add_executable(superjupiter-time-aggregate-tests tests/test.cpp)
  target_link_libraries(superjupiter-time-aggregate-tests PRIVATE SuperJupiter::TimeAggregate)
  add_test(NAME superjupiter-time-aggregate-tests COMMAND superjupiter-time-aggregate-tests)
  add_executable(superjupiter-time-aggregate-namespace-test tests/namespace_isolation.cpp)
  target_link_libraries(superjupiter-time-aggregate-namespace-test PRIVATE SuperJupiter::TimeAggregate)
  add_test(NAME superjupiter-time-aggregate-namespace-test COMMAND superjupiter-time-aggregate-namespace-test)
endif()
if(SUPERJUPITER_TIME_AGGREGATE_BUILD_EXAMPLES)
  add_executable(superjupiter-time-aggregate-replay tools/replay.cpp)
  target_link_libraries(superjupiter-time-aggregate-replay PRIVATE SuperJupiter::TimeAggregate)
endif()
if(SUPERJUPITER_TIME_AGGREGATE_INSTALL)
  include(CMakePackageConfigHelpers)
  set(_superjupiter_time_aggregate_package_dir lib/cmake/SuperJupiterTimeAggregate)
  install(TARGETS SuperJupiterTimeAggregate EXPORT SuperJupiterTimeAggregateTargets)
  install(FILES src/SuperJupiterTimeAggregate.h DESTINATION include)
  install(EXPORT SuperJupiterTimeAggregateTargets NAMESPACE SuperJupiter::
    DESTINATION ${_superjupiter_time_aggregate_package_dir})
  configure_package_config_file(cmake/SuperJupiterTimeAggregateConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/SuperJupiterTimeAggregateConfig.cmake
    INSTALL_DESTINATION ${_superjupiter_time_aggregate_package_dir})
  write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/SuperJupiterTimeAggregateConfigVersion.cmake
    VERSION ${PROJECT_VERSION} COMPATIBILITY SameMinorVersion ARCH_INDEPENDENT)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/SuperJupiterTimeAggregateConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/SuperJupiterTimeAggregateConfigVersion.cmake
    DESTINATION ${_superjupiter_time_aggregate_package_dir})
  install(FILES LICENSE DESTINATION share/licenses/SuperJupiterTimeAggregate)
endif()
