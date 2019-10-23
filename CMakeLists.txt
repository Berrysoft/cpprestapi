cmake_minimum_required(VERSION 3.7)
project(cpprestapi)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT BUILD_SHARED_LIBS)
  add_definitions(-DCPPRESTAPI_STATIC_DEFINE)
endif()

include_directories(include)
find_package(cpprestsdk CONFIG REQUIRED)

file(GLOB LIB_HEADERS "include/cpprestapi/*.hpp")
file(GLOB LIB_SOURCE "src/cpprestapi/*.cpp")
add_library(cpprestapi ${LIB_SOURCE})

target_link_libraries(cpprestapi cpprestsdk::cpprest)

install(FILES ${LIB_HEADERS} DESTINATION include/cpprestapi)
install(TARGETS cpprestapi EXPORT cpprestapi_targets LIBRARY DESTINATION lib)

include(CMakePackageConfigHelpers)

export(EXPORT cpprestapi_targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cpprestapi/cpprestapi-targets.cmake"
  NAMESPACE cpprestapi::
)
configure_file(cmake/cpprestapi-config.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/cpprestapi/cpprestapi-config.cmake"
  COPYONLY
)

set(ConfigPackageLocation lib/cpprestapi)
install(EXPORT cpprestapi_targets
  FILE
    cpprestapi-targets.cmake
  NAMESPACE
    cpprestapi::
  DESTINATION
    ${ConfigPackageLocation}
)
install(
  FILES
    cmake/cpprestapi-config.cmake
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Devel
)

file(GLOB TEST_SOURCE "test/*.cpp")
add_executable(test ${TEST_SOURCE})
target_link_libraries(test cpprestapi)
