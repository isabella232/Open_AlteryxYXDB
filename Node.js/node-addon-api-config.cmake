cmake_minimum_required(VERSION 3.9.1)

set(NODE_ADDON_API_ROOT_DIR "./node-addon-api")
set(NODE_ADDON_API_INCLUDE_DIR "${NODE_ADDON_API_ROOT_DIR}")
set(NODE_ADDON_API_LIBS "node")

include_directories(${NODE_ADDON_API_INCLUDE_DIR})
include_directories(${NODE_ADDON_API_INCLUDE_DIR}/external-napi)

list(APPEND AYX_3RD_PARTY_LIBS ${NODE_ADDON_API_LIBS})
