cmake_minimum_required(VERSION 3.9)
#Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

### Setup Directories ###
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
#Output all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

### Add External Dependencies ###
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

### Run N Gun Coursework ###
file(GLOB_RECURSE SOURCES RunNGun/*.cpp RunNGun/*.h)
add_executable(RUNNGUN ${SOURCES})
target_include_directories(RUNNGUN PRIVATE ${SFML_INCS})
target_link_libraries(RUNNGUN sfml-graphics)