cmake_minimum_required(VERSION 3.1.0)

project(Project LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

add_executable(Project
    editor.ui
    editor.cpp
    main.cpp
    editor.h
)
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>>:QT_QML_RELEASE>)
target_link_libraries(Project Qt5::Widgets)
target_link_libraries(Project Qt5::Gui)
target_link_libraries(Project Qt5::Core)