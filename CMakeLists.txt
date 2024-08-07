cmake_minimum_required(VERSION 3.9)
project(Beam-Pursuit VERSION 0.1.0)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/pinnedVector")

# Define MY_SOURCES to be a list of all the source files for my project
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp")

add_executable("${CMAKE_PROJECT_NAME}" "${MY_SOURCES}")

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    message("BUILDING DEBUG!")
    target_compile_options("${CMAKE_PROJECT_NAME}"
            PUBLIC -W -Wall -Wextra -g -Og -DDebug -pedantic -pedantic-errors)
endif()

if(CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo")
    message("BUILDING RELEASE WITH DEBUG INFO!")
    target_compile_options("${CMAKE_PROJECT_NAME}"
            PUBLIC -W -Wall -Wextra -g -O2 -DDebug -pedantic -pedantic-errors)
endif()

if(CMAKE_BUILD_TYPE MATCHES "MinSizeRel")
    message("BUILDING MINIMUM SIZE RELEASE!")
    target_compile_options("${CMAKE_PROJECT_NAME}"
            PUBLIC -DNDEBUG -Os)
endif()

if(CMAKE_BUILD_TYPE MATCHES "Release")
    message("BUILDING RELEASE!")
    target_compile_options("${CMAKE_PROJECT_NAME}"
            PUBLIC -DNDEBUG -O2)
endif()

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries("${CMAKE_PROJECT_NAME}" PUBLIC OpenMP::OpenMP_CXX)
endif()

target_link_libraries("${CMAKE_PROJECT_NAME}" PUBLIC pinnedVector)

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/res/") # This is useful to get an ASSETS_PATH in your IDE during development but you should comment this if you compile a release version and uncomment the next line
#target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./res/") # Uncomment this line to setup the ASSETS_PATH macro to the final assets directory when you share the project

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
