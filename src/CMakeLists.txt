cmake_minimum_required(VERSION 3.5)

project(algorithmic_trading VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cc
    view/main_window/main_window.cc
    view/main_window/main_window.ui
    view/graph_widget/graph_widget.cc
    view/main_window/interpolation_tab.cc
    view/main_window/approximation_tab.cc
    view/graph_widget/graph_name.cc
    common/data_struct.cc
    facade/facade.cc
    algorithms/interpolation/cubic_spline.cc
    algorithms/interpolation/newton_polynomial.cc
    algorithms/approximation/least_squares.cc
    # controlle/controller.cc
)

# file(GLOB HEADERS "main_window/*.h")

set(HEADERS
    ../common/data_struct.h
    view/main_window/main_window.h
    view/graph_widget/graph_widget.h
    view/graph_widget/style.h
    view/graph_widget/graph_name.h
    common/data_struct.h
    # controlle/controller.h
    facade/facade.h
    algorithms/interpolation/cubic_spline.h
    algorithms/interpolation/newton_polynomial.h
    algorithms/approximation/least_squares.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${PROJECT_SOURCES} ${HEADERS})
else()
    add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
        ${HEADERS}
    )
endif()
# add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/common)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/view/main_window)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/view/graph_widget)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/utility)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/facade)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/algorithms)



set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()