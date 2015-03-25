cmake_minimum_required (VERSION 2.8.11)
project (Altona2)

# detect system and architecture

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message(STATUS "OS is Windows")
    set(config_os "Windows")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(STATUS "OS is Linux")
    set(config_os "Linux")
endif()

if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    message(STATUS "Target is 64 bits")
    set(config_arch x64)
else("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    message(STATUS "Target is 32 bits")
    set(config_arch x32)
endif("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")


# automatic setup

if( ${config_os} MATCHES "Linux" )
    message(STATUS "Automatic setup for Linux")
    set(renderer gl4)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    add_definitions(-DsDEFINE_LINUX -DsDEFINE_GL4)
else()
    message(FATAL_ERROR "Automatic setup not defined on ${CMAKE_SYSTEM_NAME}...")
    # implement me
endif()


# include Altona2 root directory

set(altona2_root_dir ${CMAKE_CURRENT_LIST_DIR})
message(STATUS "Altona2 root dir is : ${altona2_root_dir}")
include_directories( ${altona2_root_dir} )

# add libraries sub-projects

add_subdirectory (Altona2/Libs/Base)
add_subdirectory (Altona2/Libs/Util)

# add examples sub-projects

add_subdirectory (Altona2/Examples/graphics/benchmark)
add_subdirectory (Altona2/Examples/graphics/cube)
add_subdirectory (Altona2/Examples/graphics/DynamicVertexUpdate)
add_subdirectory (Altona2/Examples/graphics/instances)



