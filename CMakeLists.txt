cmake_minimum_required(VERSION 3.22.1)

project(OdkExamplesCpp CXX)

set(SDK_INCLUDE_DIR  "/usr/lib/libreoffice/sdk/include"  CACHE STRING  "OO_SDK_HOME/include")
set(SDK_LIBRARY_DIR  "/usr/lib/libreoffice/sdk/lib"      CACHE STRING  "OO_SDK_HOME/lib")
set(SDK_BINARY_DIR   "/usr/lib/libreoffice/sdk/bin"      CACHE STRING  "OO_SDK_HOME/bin")
set(SDK_PROGRAM_DIR  "/usr/lib/libreoffice/program"      CACHE STRING  "OO_SDK_URE_LIB_DIR")
set(SDK_LIBRARIES    "uno_sal" "uno_salhelpergcc3" "uno_purpenvhelpergcc3" "uno_cppu" "uno_cppuhelpergcc3")
message(STATUS "Generating headers using cppumaker")
execute_process(COMMAND "${SDK_BINARY_DIR}/cppumaker" -Gc -O${PROJECT_SOURCE_DIR}/include "${SDK_PROGRAM_DIR}/types.rdb" "${SDK_PROGRAM_DIR}/types/offapi.rdb")

set(CMAKE_CXX_FLAGS            "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Wextra -pedantic -fvisibility=hidden -fpic")
set(CMAKE_CXX_FLAGS_DEBUG      "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE    "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
set(CMAKE_SHARED_LINKER_FLAGS  "-Wl,--allow-shlib-undefined -Wl,-export-dynamic -Wl,-z,defs -Wl,--no-whole-archive")
set(CMAKE_EXE_LINKER_FLAGS     "-Wl,--allow-shlib-undefined -Wl,-export-dynamic -Wl,-z,defs -Wl,--no-whole-archive")

add_compile_definitions(UNX)
add_compile_definitions(DGCC)
add_compile_definitions(LINUX)
add_compile_definitions(DCPPU_ENV=gcc3)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${SDK_INCLUDE_DIR})

add_subdirectory(FirstSteps)
add_subdirectory(ProfUNO)
add_subdirectory(Drawing)
add_subdirectory(WeakObject)
add_subdirectory(ImplHelper)
add_subdirectory(SimpleWindow)


