cmake_minimum_required(VERSION 3.9.1)

find_package( PythonLibs 3.6 REQUIRED )
include_directories( ${PYTHON_INCLUDE_DIRS} )

find_package(Boost)

set(Boost_USE_STATIC_LIBS ON)
link_directories(${BOOST_LIBRARYDIR})
message("${Boost_LIBRARIES}")
include_directories(${BOOST_INCLUDEDIR})

add_library(Python_AlteryxYXDB SHARED
  DllExport.h
  ExportPythonSDK.h
  ExportPythonSDK.cpp
)

target_link_libraries(
  Python_AlteryxYXDB
  RecordLib
  ${Boost_LIBRARIES}
  ${PYTHON_LIBRARIES}/python36.lib
)
