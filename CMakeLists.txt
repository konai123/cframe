project(cframe)
cmake_minimum_required(VERSION 3.1)

if(WIN32)
    set(Impls src/win/cframe_win_impl.cpp)
elseif(UNIX)
    set(Impls src/linux/cframe_linux_impl.cpp)
endif()

add_executable(
        ${CMAKE_PROJECT_NAME}

        src/cframe.cpp
        ${Impls}
        src/test.cpp
)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(
        ${CMAKE_PROJECT_NAME}
        PUBLIC
        src
)