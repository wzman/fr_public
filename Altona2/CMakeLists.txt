cmake_minimum_required (VERSION 2.8.11)
project (Altona2)

set(renderer gl2)

# Altona2 root dir

include_directories( /home/fred/github/fr_public/Altona2  )

# compiler flags

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lrt -g")

# user definitions

#-DsDEFINE_FINAL
#-DsDEFINE_MEMDEBUG
add_definitions( -DsDEFINE_LINUX  -DsDEFINE_GL2)

# add libraries sub-projects

add_subdirectory (Altona2/Libs/Base)
add_subdirectory (Altona2/Libs/Util)

# add examples sub-projects

add_subdirectory (Altona2/Examples/graphics/cube)



