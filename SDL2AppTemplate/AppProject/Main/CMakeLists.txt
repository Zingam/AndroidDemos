cmake_minimum_required (VERSION 3.6)

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
      #        CMAKE_FIND_ROOT_PATH
      #   set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
      #   set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
      #   set (CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)
      #   set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM BOTH)
      NO_CMAKE_FIND_ROOT_PATH
  )
  if (NOT ${IncludeDirectory})
    message (FATAL_ERROR "Cound not find ${HeaderFile} in ${searchPath}")
  endif ()
endfunction ()

project ("main")

add_library (${PROJECT_NAME} SHARED
  "Sources/main.cpp"
)

if (NOT USE_SDL2-static)
  AddImportedLibrary ("SDL2" SHARED
    "libSDL2.so"
    "${NativeLibraryArtifactsOutputDir}/sdl2lib"
  )
else()
  AddImportedLibrary ("SDL2" STATIC
    "libSDL2.a"
    "${NativeLibraryArtifactsOutputDir}/sdl2lib"
  )
endif()
AddImportedLibrary ("SDL2main" STATIC
  "libSDL2main.a"
  "${NativeLibraryArtifactsOutputDir}/sdl2lib"
)
# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
target_link_libraries (
  # Specifies the target library.
  ${PROJECT_NAME}

  # Libraries from other modules
  "SDL2"
  "SDL2main"

  # Links the target library to the libraries included in the NDK.
  "android"
  #"GLESv1_CM"
  #"GLESv2"
  "GLESv3"
  "log"
)

# Find the locations of the IMPORTED libraries' header files
FindIncludePath ("SDL2_INCLUDEDIR"
  "SDL.h"
  "${ExternalLibrariesRootDir}/SDL2/include"
)
# Make the IMPORTED libraries' header files visible in the target
target_include_directories (${PROJECT_NAME}
  PRIVATE
    ${SDL2_INCLUDEDIR}
)
