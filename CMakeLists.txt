cmake_minimum_required(VERSION 3.7)

project(app)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON )

# Enable make ninja compile color output
option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." TRUE)
if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       add_compile_options (-fcolor-diagnostics)
    endif ()
endif ()

# source
set(sources
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

if(WIN32)
  set(sources WIN32 ${sources})
endif()

# libs
if(MSVC)
  find_package(SDL2 REQUIRED)
  include_directories(${SDL2_INCLUDE_DIRS})
  set(libs ${SDL2_LIBRARIES})
else()
  set(libs SDL2main SDL2_image SDL2)
endif()
if(MINGW)
  set(libs mingw32 ${libs})
endif()

add_executable(app ${sources})
target_link_libraries(app ${libs})

# more compiler warning
if(MSVC)
  target_compile_options(app PRIVATE /W4)
else()
  target_compile_options(app PRIVATE -Wall -Wextra -pedantic)
endif()

## Enbale LTO if possible
#include(CheckIPOSupported)
#check_ipo_supported(RESULT supported OUTPUT error)
#if( supported )
#    set_property(TARGET app PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
#else()
#    message(STATUS "IPO / LTO not supported: <${error}>")
#endif()

# test_cases ----------------------
add_subdirectory(tests)