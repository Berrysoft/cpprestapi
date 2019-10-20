cmake_minimum_required(VERSION 3.7)
project(cpprestapi)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT BUILD_SHARED_LIBS)
  add_definitions(-DCPPRESTAPI_STATIC_DEFINE)
endif()

include_directories(include)
find_package(cpprestsdk CONFIG REQUIRED)

file(GLOB LIB_HEADERS "include/cpprestapi/*.hpp")
file(GLOB LIB_SOURCE "src/cpprestapi/*.cpp")
add_library(cpprestapi ${LIB_SOURCE})

target_link_libraries(cpprestapi cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_boost_internal cpprestsdk::cpprestsdk_brotli_internal)

install(FILES ${LIB_HEADERS} DESTINATION include/cpprestapi)
install(TARGETS cpprestapi LIBRARY DESTINATION lib)

file(GLOB TEST_SOURCE "test/*.cpp")
add_executable(test ${TEST_SOURCE})
target_link_libraries(test cpprestapi)
