cmake_minimum_required(VERSION 3.9.1)

add_library(Python_AlteryxYXDB SHARED
  DllExport.h
  ExportPythonSDK.h
  ExportPythonSDK.cpp
)

find_package(PythonLibs 3.6 REQUIRED)
link_directories(${PYTHON_LIBRARIES})
target_include_directories(Python_AlteryxYXDB PRIVATE ${PYTHON_INCLUDE_DIRS})

find_package(Boost)
set(Boost_USE_STATIC_LIBS ON)
link_directories(${BOOST_LIBRARYDIR})
target_include_directories(Python_AlteryxYXDB PRIVATE ${BOOST_INCLUDEDIR})

target_link_libraries(
  Python_AlteryxYXDB
  Open_AlteryxYXDB
  ${PYTHON_LIBRARIES}/python36.lib
  ${BOOST_LIBRARYDIR}/libboost_python-vc140-mt-gd-1_62.lib
)

file(TO_NATIVE_PATH ${CMAKE_CURRENT_BINARY_DIR} native_binary_dir)

add_custom_command(TARGET Python_AlteryxYXDB POST_BUILD
  COMMAND copy "${native_binary_dir}\\Output\\Debug\\Python_AlteryxYXDB.dll" "${native_binary_dir}\\Output\\Debug\\Python_AlteryxYXDB.pyd"
)
