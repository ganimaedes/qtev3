cmake_minimum_required(VERSION 3.04)
project(qwtq)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

set(Qwt_DIR "/usr/include/qwt")

# Find the Qt5Xml library
find_package(Qt5Xml)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Cmake/Modules/")

find_package(Qwt)
include_directories(.)

include_directories(${QWT_LIBRARY})
include_directories(${Qwt_DIR})

set(EV3 "/home/ubuntu-gnome/qwtq/ev3")
include_directories(${EV3})

file(GLOB HEADERS *.h ${EV3}/*.h)
file(GLOB SOURCES *.cpp ${EV3}/*.cpp)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_COMPILER ".../cquery/build/clang+llvm-6.0.1-x86_64-linux-gnu-ubuntu-16.04/bin/clang++")
set(CMAKE_SHARED_LINKER_FLAGS "-lstdc++ -Wl,--no-as-needed -ldl -lqwt -v")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CMAKE_SHARED_LINKER_FLAGS}")

set(qwt_libraries ${QWT_LIBRARY}) 

qt5_add_resources(RSC completer.qrc)
set_property(SOURCE qrc_completer.cpp PROPERTY SKIP_AUTOMOC ON) 
add_executable(qwtq ${HEADERS} ${SOURCES} ${RSC}) 

# The Qt5Widgets_INCLUDES also includes the include directories for
  # dependencies QtCore and QtGui
  include_directories(${Qt5Widgets_INCLUDES})
  include_directories(${Qt5Xml_INCLUDES})
  
  include_directories(${Qt5Widgets_INCLUDE_DIRS})
  include_directories(${Qwt_INCLUDE_DIRS})
  include_directories(${Qt5Xml_INCLUDES_DIRS})

  # We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
  add_definitions(${Qt5Widgets_DEFINITIONS})
  add_definitions(${Qt5Xml_DEFINITIONS})

  # Executables fail to build with Qt 5 in the default configuration
  # without -fPIE. We add that here.
  set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

# Use the Widgets module from Qt 5.
target_link_libraries(qwtq Qt5::Widgets Qt5::Xml ${qwt_libraries})
