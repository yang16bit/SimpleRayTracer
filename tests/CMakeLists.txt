cmake_minimum_required( VERSION 3.0 )

project( catch_testcases CXX )

#get_filename_component(DIR_PARENT ${CMAKE_CURRENT_SOURCE_DIR} PATH)

set( SOURCES_VECTOR
        vector.cpp
        ../Vector.cpp
        )

set( SOURCES_MATRIX
        matrix.cpp
        ../Matrix.cpp
        ../Vector.cpp
        )

set( SOURCES_MATRIX2
        matrix2.cpp
        ../Matrix2.cpp
        ../Vector2.cpp
        )


set( SOURCES_ALL_TARGET
        SOURCES_VECTOR
        SOURCES_MATRIX
        SOURCES_MATRIX2
)

set( SOURCE_MAIN catch_main.cpp )

foreach(TARGET_SRC ${SOURCES_ALL_TARGET})
    string( REPLACE "SOURCES_" "TestCase_" EXECUTABLE_NAME "${TARGET_SRC}")
    add_executable(${EXECUTABLE_NAME} ${${TARGET_SRC}} ${SOURCE_MAIN})
endforeach()