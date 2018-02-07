cmake_minimum_required(VERSION 3.9.1)

project(Open_AlteryxYXDB)

set(CMAKE_CXX_STANDARD 14)

IF(MSVC)
  add_definitions	(
    # /DE2
    # /DE2WINDOWS
    /W4 /WX /GR /EHa /MP /Gm- /J
    /DWIN32
    /D_WIN32
    /D_WINDOWS
    -D_ENABLE_ATOMIC_ALIGNMENT_FIX
    -DNOMINMAX
    -DUNICODE
    -D_UNICODE
  )
ENDIF()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "Output")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "Output")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "Output")

add_subdirectory(liblzf-3.6 Output/liblzf-3.6)
add_subdirectory(RecordLib Output/RecordLib)

add_library(Open_AlteryxYXDB
  Open_AlteryxYXDB.cpp
  Open_AlteryxYXDB.h
  SrcLib_Replacement.h
  stdafx.cpp
  stdafx.h
)

target_include_directories(Open_AlteryxYXDB PUBLIC RecordLib)
target_include_directories(Open_AlteryxYXDB PUBLIC liblzf-3.6)

target_link_libraries(
  Open_AlteryxYXDB
  RecordLib
)

add_subdirectory(Python Output/Python)

add_executable(Test
  Test.cpp
  stdafx.cpp
  stdafx.h
)

target_link_libraries(Test
  Open_AlteryxYXDB
)
