cmake_minimum_required(VERSION 3.11 FATAL_ERROR)



project(NovaRelease LANGUAGES CXX)
add_executable(${PROJECT_NAME} "main.cpp" "mainwindow.hpp" "mainwindow.cpp" "mainwindow.hpp" "mainwindow.ui" "secondwindow.ui" "secondwindow.hpp" "secondwindow.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
    )
target_compile_features(${PROJECT_NAME}
PRIVATE cxx_std_17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(libnova REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets libnova::libnova)
