# Util library

project (Util)

add_library ( ${PROJECT_NAME}
Scanner.cpp
DebugPainter.cpp
Autosave.cpp
Painter.cpp
GraphicsHelper.cpp
Image.cpp
#mp.txt";
SampleMixer.cpp
TextureFont.cpp
#UtilShaders.asc";
#UtilShaders.hpp
Config.cpp
Compression.cpp
IconManager.cpp

StbImage.c
StbVorbis.c
StbImageWrite.h
StbDxt.h
)


# build .asc files in project directory, add dependencies and link

file(GLOB asc_files "${CMAKE_CURRENT_SOURCE_DIR}/*.asc")
foreach(file ${asc_files})
    get_filename_component(basename ${file} NAME_WE)
    set(target "${PROJECT_NAME}_${basename}")
    set(outobj "${CMAKE_CURRENT_BINARY_DIR}/${basename}.o")
    set(outhpp "${CMAKE_CURRENT_SOURCE_DIR}/${basename}.hpp")
    add_custom_target(
        ${target}
        COMMAND asc -i=${file}
                    -o=${outobj}
                    -h=${outhpp}
                    -p=${renderer} -x64
    )
    add_dependencies(${PROJECT_NAME} ${target})
    target_link_libraries(${PROJECT_NAME} LINK_PRIVATE ${outobj} )
endforeach()

# Make sure the compiler can find include files for our Util library
# when other libraries or executables link to Util

target_include_directories (Util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})



