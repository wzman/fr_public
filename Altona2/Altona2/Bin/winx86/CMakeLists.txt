cmake_minimum_required (VERSION 2.8.11)
project (Altona2_Tools)

# Altona2 root dir
set(altona2_root_dir "C:/github/fr_public/Altona2" CACHE FILEPATH "Altona2 root directory")

# shared obj
file( GLOB objlib
${altona2_root_dir}/Altona2/Libs/Base/Containers.cpp
${altona2_root_dir}/Altona2/Libs/Base/Graphics.cpp
${altona2_root_dir}/Altona2/Libs/Base/GraphicsNull.cpp
${altona2_root_dir}/Altona2/Libs/Base/Machine.cpp
${altona2_root_dir}/Altona2/Libs/Base/String.cpp
${altona2_root_dir}/Altona2/Libs/Base/System.cpp
${altona2_root_dir}/Altona2/Libs/Base/Wintab.cpp
${altona2_root_dir}/Altona2/Libs/Base/SystemWin.cpp
${altona2_root_dir}/Altona2/Libs/Base/SystemPosix.cpp
${altona2_root_dir}/Altona2/Libs/Base/Types.cpp
${altona2_root_dir}/Altona2/Libs/Base/Math.cpp
${altona2_root_dir}/Altona2/Libs/Util/Scanner.cpp
${altona2_root_dir}/Altona2/Libs/Base/Serialize.cpp
${altona2_root_dir}/Altona2/Libs/Base/Perfmon.cpp
${altona2_root_dir}/Altona2/Libs/Base/DxShaderCompiler.cpp
)

# inbin obj
file( GLOB objincbin
${altona2_root_dir}/Altona2/Tools/Incbin/Main.cpp
)

# asc obj
file( GLOB objasc
${altona2_root_dir}/Altona2/Tools/Asc/Asc.cpp
${altona2_root_dir}/Altona2/Tools/Asc/Doc.cpp
${altona2_root_dir}/Altona2/Tools/Asc/Hlsl.cpp
${altona2_root_dir}/Altona2/Tools/Asc/Glsl.cpp
${altona2_root_dir}/Altona2/Tools/Asc/Main.cpp
)

# packfile obj
file( GLOB objpackfile
${altona2_root_dir}/Altona2/Tools/Packfile/Doc.cpp
${altona2_root_dir}/Altona2/Tools/Packfile/Main.cpp
)

# makeproject obj
file( GLOB objmp
${altona2_root_dir}/Altona2/Tools/MakeProject/Doc.cpp
${altona2_root_dir}/Altona2/Tools/MakeProject/DocMake.cpp
${altona2_root_dir}/Altona2/Tools/MakeProject/DocVs2008.cpp
${altona2_root_dir}/Altona2/Tools/MakeProject/DocVs2010.cpp
${altona2_root_dir}/Altona2/Tools/MakeProject/DocVs2012.cpp
${altona2_root_dir}/Altona2/Tools/MakeProject/DocXcode4.cpp
${altona2_root_dir}/Altona2/Tools/MakeProject/DocNdk.cpp
${altona2_root_dir}/Altona2/Tools/MakeProject/Main.cpp
)

# set same output directory for all project
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/BUILD)
set(outputdirectory ${EXECUTABLE_OUTPUT_PATH})
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${outputdirectory} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${outputdirectory} )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${outputdirectory} )
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${outputdirectory} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${outputdirectory} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${outputdirectory} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

# detect x32 or x64
if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    set(config_arch x64)
else("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    set(config_arch x32)
endif("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")

# set compiler flags, def and include dir
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_definitions(-DWIN32 -DUNICODE -DsDEFINE_SHELL -DsDEFINE_MEMDEBUG)
include_directories( ${altona2_root_dir} )

# build shared altona2 library
add_library (altonalib ${objlib})
target_include_directories (altonalib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# build incbin
add_executable( incbin2 ${objincbin} )
target_link_libraries( incbin2 LINK_PUBLIC altonalib)

# build asc
add_executable( asc2 ${objasc} )
target_link_libraries( asc2 LINK_PUBLIC altonalib)

# build packfile
add_executable( packfile ${objpackfile} )
target_link_libraries( packfile LINK_PUBLIC altonalib)

# copy Incbin.incbin and config files from Tools/MakeProject to output build directory
set(inc_file "${altona2_root_dir}/Altona2/Tools/MakeProject/Incbin.incbin")
file(GLOB inc_needed_files
  "${altona2_root_dir}/Altona2/Tools/MakeProject/*.txt"
  ${inc_file}
)
file(COPY ${inc_needed_files} DESTINATION ${outputdirectory})

# build incbin obj
get_filename_component(basename ${inc_file} NAME_WE)
set(target "makeproject_${basename}")
set(outobj "${outputdirectory}/${basename}.o")
add_custom_target(
    ${target}		
    COMMAND incbin2 -i=${inc_file} -o=${outobj} -${config_arch}
	DEPENDS ${inc_file}
	WORKING_DIRECTORY ${outputdirectory}
)

# build makeproject
add_executable( makeproject2 ${objmp} )
add_dependencies( makeproject2 ${target} )
target_link_libraries( makeproject2 LINK_PUBLIC altonalib ${outobj} )


