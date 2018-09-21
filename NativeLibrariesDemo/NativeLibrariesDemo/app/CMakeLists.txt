# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

################################################################################

# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required (VERSION 3.4.1)

################################################################################
# Function:
#   AddImportedLibrary (ImportedTargetName
#                       SHARED | STATIC
#                       LibraryName
#                       LibrarySearchPath
#   )
# Description:
#   Creates an IMPORTED library
################################################################################
function (AddImportedLibrary ImportedTargetName LibraryType LibraryName LibrarySearchPath)
  list (APPEND options "SHARED" "STATIC")
  if (NOT ${LibraryType} IN_LIST options)
    message (FATAL_ERROR "Parameter SHARED or STATIC is required, found: ${LibraryType}")
  endif ()
  add_library (${ImportedTargetName} ${LibraryType} IMPORTED)
  file (TO_CMAKE_PATH
    ${LibrarySearchPath}/${LibraryName}
    importedLibraryFile
  )
  set_property (TARGET ${ImportedTargetName}
    PROPERTY
      IMPORTED_LOCATION ${importedLibraryFile}
  )
  if (NOT TARGET ${ImportedTargetName})
    message (FATAL_ERROR "===> Imported library ${ImportedTargetName}: file not found ${importedLibraryFile}")
  endif ()
endfunction()

################################################################################
# Function:
#   FindIncludePath (IncludeDirectory
#                    HeaderFile
#                    HeaderFileSearchPath
#   )
# Description:
#   Creates an IMPORTED library
################################################################################
function (FindIncludePath IncludeDirectory HeaderFile HeaderFileSearchPath)
  file (TO_CMAKE_PATH
    ${HeaderFileSearchPath}
    searchPath
  )
  find_path (${IncludeDirectory}
    NAMES
      ${HeaderFile}
    HINTS
      ${searchPath}
    # Let CMake search in non-NDK (host system) paths as we are cross-compiling.
    # By default CMake searches only in paths defined by the Android toolchain.
    # Also see:
    #   set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
    #   set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
    #   set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)
    NO_CMAKE_FIND_ROOT_PATH
)
  if (NOT ${IncludeDirectory})
    message (FATAL_ERROR "Cound not find ${HeaderFile} in ${searchPath}")
  endif ()
endfunction ()

################################################################################

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
add_library (
  # Sets the name of the library.
  native-lib
  # Sets the library as a shared library.
  SHARED
  # Provides a relative path to your source file(s).
  src/main/cpp/native-lib.cpp
)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.
find_library (
  # Sets the name of the path variable.
  log-lib
  # Specifies the name of the NDK library that you want CMake to locate.
  log
)

################################################################################

# Aditional native libraries are created and compiled as separate library
# modules. They need to be added as IMPORTED libraries
AddImportedLibrary (ExternalSharedLibrary SHARED
  "libExternalSharedLibrary.so"
  "${NativeLibraryArtifactsOutputDir}/externalsharedlibrary"
  )
AddImportedLibrary (ExternalStaticLibrary STATIC
  "libExternalStaticLibrary.a"
  "${NativeLibraryArtifactsOutputDir}/externalstaticlibrary"
  )
AddImportedLibrary (NativeSharedLibrary SHARED
  "libNativeSharedLibrary.so"
  "${NativeLibraryArtifactsOutputDir}/nativesharedlibrary"
)
AddImportedLibrary (NativeStaticLibrary STATIC
  "libNativeStaticLibrary.a"
  "${NativeLibraryArtifactsOutputDir}/nativestaticlibrary"
)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
target_link_libraries (
  # Specifies the target library.
  native-lib

  # Libraries from other modules
  ExternalSharedLibrary
  ExternalStaticLibrary
  NativeSharedLibrary
  NativeStaticLibrary

  # Links the target library to the log library included in the NDK.
  ${log-lib}
)

# Find the locations of the IMPORTED libraries' header files
FindIncludePath (externalSharedLibrary_INCLUDEDIR
  "ExternalSharedLibrary.hpp"
  "${ExternalLibrariesRootDir}/ExternalSharedLibrary/Sources"
)
FindIncludePath (externalStaticLibrary_INCLUDEDIR
  "ExternalStaticLibrary.hpp"
  "${ExternalLibrariesRootDir}/ExternalStaticLibrary/Sources"
)
FindIncludePath (nativeSharedLibrary_INCLUDEDIR
  "NativeSharedLibrary.hpp"
  "${RootDir}/nativesharedlibrary/src/main/jni"
)
FindIncludePath (nativeStaticLibrary_INCLUDEDIR
  "NativeStaticLibrary.hpp"
  "${RootDir}/nativestaticlibrary/src/main/jni"
)
# Make the IMPORTED libraries' header files visible in the target
target_include_directories (native-lib
  PRIVATE
    ${externalSharedLibrary_INCLUDEDIR}
    ${externalStaticLibrary_INCLUDEDIR}
    ${nativeSharedLibrary_INCLUDEDIR}
    ${nativeStaticLibrary_INCLUDEDIR}
)
