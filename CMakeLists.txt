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

add_subdirectory(liblzf-3.6 Output/liblzf-3.6)
add_subdirectory(RecordLib Output/RecordLib)

include_directories(liblzf-3.6)
include_directories(RecordLib)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "Output")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "Output")

add_library(Open_AlteryxYXDB
  Open_AlteryxYXDB.cpp
  stdafx.cpp
)

target_link_libraries(
  Open_AlteryxYXDB
  RecordLib
  liblzf-3.6
)

add_executable(Test
  Test.cpp
  stdafx.cpp
)

target_link_libraries(Test
  liblzf-3.6
  RecordLib
  Open_AlteryxYXDB
)
