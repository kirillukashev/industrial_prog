cmake_minimum_required(VERSION 3.10)
project(CurvesFilter)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(MAP_PNG_URL "https://raw.githubusercontent.com/magdasta/instagram-7.7.-decompiled-/master/assets/filters/lo_fi/map.png")
set(MAP_PNG "${CMAKE_CURRENT_BINARY_DIR}/map.png")
set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(LUT_HEADER "${GENERATED_DIR}/lut_data.h")
set(LUT_SOURCE "${GENERATED_DIR}/lut_data.cpp")

add_custom_command(
    OUTPUT "${MAP_PNG}" "${LUT_HEADER}" "${LUT_SOURCE}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${GENERATED_DIR}"
    COMMAND ${CMAKE_COMMAND}
            -DURL=${MAP_PNG_URL}
            -DDEST=${MAP_PNG}
            -P "${CMAKE_CURRENT_SOURCE_DIR}/download_if_missing.cmake"
    COMMAND "${Python3_EXECUTABLE}"
            "${CMAKE_CURRENT_SOURCE_DIR}/generate_lut.py"
            "${MAP_PNG}"
            "${LUT_HEADER}"
            "${LUT_SOURCE}"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/generate_lut.py"
            "${CMAKE_CURRENT_SOURCE_DIR}/download_if_missing.cmake"
    COMMENT "Downloading map.png and generating LUT"
    VERBATIM
)

add_executable(curves main.cpp "${LUT_SOURCE}")
target_include_directories(curves PRIVATE "${GENERATED_DIR}" ${OpenCV_INCLUDE_DIRS})
target_link_libraries(curves ${OpenCV_LIBS})
target_compile_definitions(curves PRIVATE DEFAULT_MAP_PATH=\"${MAP_PNG}\")
