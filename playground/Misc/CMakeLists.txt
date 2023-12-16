cmake_minimum_required(VERSION 3.23)

file(GLOB misc_files "shapes/*")

foreach(file ${misc_files})
    file(RELATIVE_PATH relative_file ${CMAKE_CURRENT_SOURCE_DIR} ${file})
    configure_file(${relative_file} ${relative_file})
endforeach()
