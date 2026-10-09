cmake_minimum_required(VERSION 3.16)

project(OpenCVProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Image.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        include
        ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${OpenCV_LIBS}
)
