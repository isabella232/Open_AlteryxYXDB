cmake_minimum_required(VERSION 3.9.1)

include_directories(..)

add_library(RecordLib
  FieldBase.cpp
  Record.cpp
)

target_link_libraries(RecordLib liblzf-3.6)
