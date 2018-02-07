cmake_minimum_required(VERSION 3.9.1)

IF(MSVC)
  add_definitions	(
    /W0
  )
ENDIF()

add_library(liblzf-3.6
  config.h
  crc32.h
  lzf_c.c
  lzf_d.c
  lzfP.h
)
