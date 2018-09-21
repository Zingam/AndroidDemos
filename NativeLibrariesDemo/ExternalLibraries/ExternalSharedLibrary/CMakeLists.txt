cmake_minimum_required (VERSION 3.6)

project ("ExternalSharedLibrary")

add_library (${PROJECT_NAME} SHARED
  "Sources/ExternalSharedLibrary.cpp"
  "Sources/ExternalSharedLibrary.hpp"
)
