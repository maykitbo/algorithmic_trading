cmake_minimum_required(VERSION 3.0)

project(utility VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_COMPILER g++)


# List your utility source files
set(SOURCES
    dummy.cc
)

# List your utility header files
file(GLOB HEADERS "*.h")


add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
# target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
