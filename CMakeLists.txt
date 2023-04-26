cmake_minimum_required(VERSION 3.14)

project(hd_doxygen_parser_plugin LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(
  hd_doxygen_parser_plugin SHARED
  hd_doxygen_parser_plugin.cpp hd_doxygen_parser_plugin.h
  rz_header_docu_plugins.h)

target_link_libraries(hd_doxygen_parser_plugin
                      PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(hd_doxygen_parser_plugin
                           PRIVATE HD_DOXYGEN_PARSER_PLUGIN_LIBRARY)
