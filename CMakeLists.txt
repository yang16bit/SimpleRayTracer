cmake_minimum_required(VERSION 3.7)
project(app)

set(CMAKE_CXX_STANDARD 14)

if(NOT MSVC)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif(NOT MSVC)

# ----------------------
set(SOURCE_FILES
        main.cpp
        GameWindow.cpp
        Window.cpp
        Scene.cpp
        Camera.cpp
        Visible.cpp
        Sphere.cpp
        Triangle.cpp
        Vector.cpp
        Matrix.cpp
        Image24.cpp
        Polygon.cpp
        Matrix2.cpp
        Vector2.cpp
        Light.cpp
        SpotLight.cpp
        ParallelLight.cpp
        )

add_executable(app WIN32
        ${SOURCE_FILES})

target_link_libraries(app
        winmm)

# test_cases ----------------------
add_subdirectory(tests)