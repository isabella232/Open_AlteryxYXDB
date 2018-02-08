cmake_minimum_required(VERSION 3.9.1)

# list(APPEND CMAKE_PREFIX_PATH "${AYX_ROOT_DIR}/3rdParty/CMakePackages/")

find_package(node-addon-api)
find_package(napi-thread-safe-callback)

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

target_link_libraries(NodeJS_AlteryxYXDB ${AYX_3RD_PARTY_LIBS} ${AYX_LIBS})

target_sources(NodeJS_AlteryxYXDB
  PRIVATE ${SOURCES}
  PRIVATE ${HEADERS}
)
