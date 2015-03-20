# Base library

project (Base)

add_library ( ${PROJECT_NAME}

Containers.cpp
Graphics.cpp
Math.cpp
Perfmon.cpp
Serialize.cpp
String.cpp
System.cpp
SystemPrivate.hpp
#Types.cpp
#Types2.cpp
#Wintab.cpp
#Wintab.h

SystemLinux.cpp
SystemPosix.cpp

GraphicsGl2.cpp
GraphicsGlew.cpp

Machine.cpp
#Base.hpp


Types2.hpp
Types.cpp
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


# Make sure the compiler can find include files for our Base library
# when other libraries or executables link to Base

target_include_directories (Base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
