cmake_minimum_required(VERSION 3.18)

project(roboflex_visualization)

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
    ${SDL2_INCLUDE_DIRS}
)

# Link against the necessary libraries
target_link_libraries(roboflex_visualization PUBLIC 
    roboflex_core 
    ${SDL2_LIBRARIES}
)


# -------------------- 
# Examples

# display_static_cpp example
add_executable(display_static_cpp examples/display_static_cpp.cpp)
target_link_libraries(display_static_cpp PRIVATE 
    roboflex_core 
    roboflex_visualization
)

# display_black_and_white_static_cpp example
add_executable(display_black_and_white_static_cpp examples/display_black_and_white_static_cpp.cpp)
target_link_libraries(display_black_and_white_static_cpp PRIVATE 
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
