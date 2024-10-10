cmake_minimum_required(VERSION 3.27)

project(aircalc VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH bin/)

if(CMAKE_VERSION VERSION_LESS 3.7.0)
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

include_directories(src/include/)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

add_executable(aircalc WIN32
  src/include/application.hpp
  src/include/mainwindow.hpp
  src/include/vtabwidget.hpp
  src/include/vtabbar.hpp
  src/include/formulawidget.hpp
  src/include/parameditwidget.hpp
  src/include/formula.hpp
  src/main.cpp
  src/application.cpp
  src/mainwindow.cpp
  src/vtabwidget.cpp
  src/vtabbar.cpp
  src/formulawidget.cpp
  src/parameditwidget.cpp
  src/formula.cpp
  resources.qrc
)

target_link_libraries(aircalc Qt5::Core Qt5::Widgets Qt5::Gui)
