cmake_minimum_required (VERSION 2.8)
project (rtlib-gui)

# Packages.
find_package(metasim REQUIRED)
find_package(rtlib REQUIRED)

#find_package(Qt5Core)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets REQUIRED)

# set metasim include dir
set(metasim_INCLUDE_DIRS "${metasim_DIR}/../../src")
set(rtlib_INCLUDE_DIRS "${rtlib_DIR}/../src")

# Include dirs.
include_directories(.)
include_directories(${rtlib_INCLUDE_DIRS})
include_directories(${metasim_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})

# Executable
file(GLOB gui_SRC "*.cpp" "*.hpp" "*.qrc")

add_executable(rtlib-gui ${gui_SRC})

target_link_libraries(rtlib-gui  rtlib metasim Qt5::Widgets)

set_property(TARGET rtlib-gui PROPERTY CXX_STANDARD 11)
set_property(TARGET rtlib-gui PROPERTY CXX_STANDARD_REQUIRED ON)

# Export.
#export(TARGETS rtlib-gui FILE "./rtlib-guiConfig.cmake")
#export(PACKAGE rtlib-gui)
