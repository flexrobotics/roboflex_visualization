cmake_minimum_required(VERSION 3.25)

project(roboflex_visualization VERSION 0.1.0 DESCRIPTION "roboflex visualization tools using simple directmedia layer")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# -------------------- 
# Resolve dependencies

include(FetchContent)

find_package(SDL2 REQUIRED)

# Locate the installed roboflex_core and its dependencies
# download and build roboflex_core
FetchContent_Declare(roboflex_core
    GIT_REPOSITORY https://github.com/flexrobotics/roboflex.git
    GIT_TAG        main
)
set(BUILD_ROBOFLEX_PYTHON_EXT OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(roboflex_core)




# -------------------- 
# Define the library

add_library(roboflex_visualization STATIC
    src/visualization.cpp
    include/roboflex_visualization/visualization.h
)

# Set some properties on our library
set_property(TARGET roboflex_visualization PROPERTY 
    POSITION_INDEPENDENT_CODE ON
)

# Include directories when we compile our library
target_include_directories(roboflex_visualization PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
    $<INSTALL_INTERFACE:include>
)

# Link against the necessary libraries
target_link_libraries(roboflex_visualization PUBLIC 
    roboflex_core 
    SDL2

    # Unfortunately, we need to link against all these libraries
    # because they are used by roboflex_core, and cmake doesn't
    # seem to be transitivily doing it's thing. Urgh, someone help.
    flatbuffers_util 
    xtensor 
    xsimd 
    xtl
    Eigen3::Eigen
)


# -------------------- 
# Examples

# basic_0 example
add_executable(display_static_cpp examples/display_static_cpp.cpp)
target_link_libraries(display_static_cpp PRIVATE 
    roboflex_core 
    roboflex_visualization
)


# -------------------- 
# install

# If you need to install the visualization library
install(TARGETS roboflex_visualization 
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/roboflex_visualization
    DESTINATION include
)


# --------------------
# build python bindings

add_subdirectory(python)
