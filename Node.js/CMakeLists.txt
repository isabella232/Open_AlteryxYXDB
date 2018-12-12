cmake_minimum_required(VERSION 3.9.1)
set( AYX_ROOT_DIR "S:\\")
include("S:\\3rdParty\\CMakePackages\\napi-thread-safe-callback-config.cmake")
include("S:\\3rdParty\\CMakePackages\\node-addon-api-config.cmake")

#find_package(node-addon-api)
#find_package(napi-thread-safe-callback)

set(SOURCES
  n-api-sandbox.cpp
)

set(HEADERS
  n-api-sandbox.h
)

link_directories(".") # HACK to get temporary node.lib in the linker path

add_library(NodeJS_AlteryxYXDB SHARED
  ${SOURCES}
  ${HEADERS}
)

set_target_properties(NodeJS_AlteryxYXDB PROPERTIES PREFIX "" SUFFIX ".node")

target_link_libraries(NodeJS_AlteryxYXDB
  Open_AlteryxYXDB
  ${AYX_3RD_PARTY_LIBS}
  ${AYX_LIBS}
)

target_sources(NodeJS_AlteryxYXDB
  PRIVATE ${SOURCES}
  PRIVATE ${HEADERS}
)
