cmake_minimum_required (VERSION 3.6)

project (NativeStaticLibrary)

add_library (${PROJECT_NAME} STATIC
  "src/main/jni/NativeStaticLibrary.cpp"
  "src/main/jni/NativeStaticLibrary.hpp"
)
