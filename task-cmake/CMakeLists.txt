cmake_minimum_required(VERSION 3.10)
project(IndustrialProg)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python3 REQUIRED COMPONENTS Interpreter)
execute_process(
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/A/preparing.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE PREPARE_RESULT
)
if(NOT PREPARE_RESULT EQUAL 0)
    message(FATAL_ERROR "preparing.py failed with code ${PREPARE_RESULT}")
endif()

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_subdirectory(B)

add_executable(C C/main.cpp)
target_include_directories(C PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(C lib)
set_target_properties(C PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

find_package(GTest REQUIRED)
add_executable(CTest C/main_test.cpp C/test_cases.cpp)
target_include_directories(CTest PRIVATE ${CMAKE_SOURCE_DIR} ${GTEST_INCLUDE_DIRS})
target_link_libraries(CTest lib ${GTEST_BOTH_LIBRARIES} pthread)
set_target_properties(CTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
