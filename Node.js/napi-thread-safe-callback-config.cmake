cmake_minimum_required(VERSION 3.9.1)

set(LIBUV_ROOT_DIR "./libuv")
set(LIBUV_INCLUDE_DIR "${LIBUV_ROOT_DIR}/include")

# TSC = thread-safe-callback
set(NAPI_TSC_ROOT_DIR "./napi-thread-safe-callback")
set(NAPI_TSC_INCLUDE_DIR "${NAPI_TSC_ROOT_DIR}")

include_directories(${LIBUV_INCLUDE_DIR} ${NAPI_TSC_INCLUDE_DIR})
