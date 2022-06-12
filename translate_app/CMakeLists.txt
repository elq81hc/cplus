cmake_minimum_required(VERSION 3.0.0)
project(translate VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)

add_executable(translate main.cpp json11/json11.cpp)

set_target_properties(translate
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
