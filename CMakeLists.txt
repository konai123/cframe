project(cframe)
cmake_minimum_required(VERSION 3.1)

add_executable(
        ${CMAKE_PROJECT_NAME}
        src/cframe.cpp
        src/win/cframe_win_impl.cpp

        src/test.cpp
)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(
        ${CMAKE_PROJECT_NAME}
        PUBLIC
        src
)