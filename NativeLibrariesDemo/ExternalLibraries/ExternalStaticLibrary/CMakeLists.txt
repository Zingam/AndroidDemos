cmake_minimum_required (VERSION 3.6)

project ("ExternalStaticLibrary")

add_library (${PROJECT_NAME} STATIC
  "Sources/ExternalStaticLibrary.cpp"
  "Sources/ExternalStaticLibrary.hpp"
)

target_include_directories (${PROJECT_NAME}
  INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}"
)
