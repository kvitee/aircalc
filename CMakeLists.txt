cmake_minimum_required(VERSION 3.27)

project(aircalc VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH bin/)

if(CMAKE_VERSION VERSION_LESS 3.7.0)
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

include_directories(src/include/)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Core Widgets Gui REQUIRED)

add_executable(aircalc WIN32
  # Headers
  src/include/application.hpp
  src/include/mainwindow.hpp
  src/include/formulas_calculator.hpp
  src/include/labeled_line_edit.hpp
  # Sources
  src/main.cpp
  src/application.cpp
  src/mainwindow.cpp
  src/formulas_calculator.cpp
  src/labeled_line_edit.cpp
)

target_link_libraries(aircalc Qt6::Core Qt6::Widgets Qt6::Gui)
