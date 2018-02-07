cmake_minimum_required(VERSION 3.9.1)

include_directories(..)

add_library(RecordLib
  DateTimeValidate.h
  FieldBase.cpp
  FieldBase.h
  FieldTypes.h
  Record.cpp
  Record.h
  RecordObj.h
)

target_link_libraries(RecordLib liblzf-3.6)
