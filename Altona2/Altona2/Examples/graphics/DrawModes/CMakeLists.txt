project (DrawModes)

add_executable ( ${PROJECT_NAME}
main.cpp
main.hpp
shader.asc
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
                    -p=${renderer} -${config_arch}
    )
    add_dependencies(${PROJECT_NAME} ${target})
    target_link_libraries(${PROJECT_NAME} LINK_PRIVATE ${outobj} )
endforeach()


# link project libraries

target_link_libraries (${PROJECT_NAME} LINK_PUBLIC Base)
target_link_libraries (${PROJECT_NAME} LINK_PUBLIC Util)
