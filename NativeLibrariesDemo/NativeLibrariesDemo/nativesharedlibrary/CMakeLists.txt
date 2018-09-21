cmake_minimum_required (VERSION 3.6)

project (NativeSharedLibrary)

add_library (${PROJECT_NAME} SHARED
  "src/main/jni/NativeSharedLibrary.cpp"
  "src/main/jni/NativeSharedLibrary.hpp"
)
