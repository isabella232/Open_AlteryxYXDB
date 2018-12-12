cmake_minimum_required(VERSION 3.13.0)

add_library(Python_AlteryxYXDB SHARED
  DllExport.h
  ExportPythonSDK.cpp
  ExportPythonSDK.h
  Field.cpp
  Field.h
  RecordCreator.cpp
  RecordCreator.h
  RecordInfo.cpp
  RecordInfo.h
)

find_package(Python3 COMPONENTS Development)
link_directories(${Python3_LIBRARIES})
target_include_directories(Python_AlteryxYXDB PUBLIC ${Python3_INCLUDE_DIRS})


set(Boost_DEBUG 1)
set( BOOST_ROOT "S:\\3rdParty\\Utility\\boost_1_62_0")
set( BOOST_DIR "S:\\3rdParty\\Utility\\boost_1_62_0")
set( BOOST_LIBRARYDIR "S:\\3rdParty\\Utility\\boost_1_62_0\\stage\\lib_x64\\lib" )
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS python3)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIR})
endif()

target_include_directories(Python_AlteryxYXDB PUBLIC ${BOOST_INCLUDEDIR})

target_link_libraries(
  Python_AlteryxYXDB
  Open_AlteryxYXDB
  ${Python3_LIBRARIES}
  Boost::python3
)

file(TO_NATIVE_PATH ${CMAKE_CURRENT_BINARY_DIR} native_binary_dir)

add_custom_command(TARGET Python_AlteryxYXDB POST_BUILD
  COMMAND copy "${native_binary_dir}\\Output\\Debug\\Python_AlteryxYXDB.dll" "${native_binary_dir}\\Output\\Debug\\Python_AlteryxYXDB.pyd"
)
