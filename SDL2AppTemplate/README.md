SDL2AppTemplate
==============

```
    printf("SDL2 application template for Android")
```

## Project structure

--+- AppProject
  |   +- Main
  |       +- Sources
  |           +- main.cpp                <-- Android application (C/C++ sources)
  |      CMakeLists.txt
  +- ExternalLibraries
  |   +- SDL2                            <-- SDL2 library sources (C sources)
  +- SDL2AppTemplate
      |  ...
      +- sdl2app                         <-- Android application (Java sources)
          +- ...
         sdl2lib                         <-- Android SDL2 library (Java sources)
          +- ...

# Project structure description

* Android application (C/C++ sources) - The C/C++ source files for the
  `libmain.so` library
* SDL2 library sources (C sources) - Original source distribution
* Android application (Java sources) - Produces the `libmain.so`, which is
  loaded at runtime by the Android Java wrapper for SDL2 library
* Android SDL2 library (Java sources) - Android Java wrapper for the SDL2
  library
  
# Development notes
1. To write an application put new source files to /AppProject/Main/Sources and
   add them to */AppProject/MainCMakeLists.txt* file as necessary.
2. To extend the SDL2 Java wrapper functionality edit `class MainActivity` in
   */SDL2AppTemplate/sdl2app/src/main/java/com/roccoormm/sdl2app/MainActivity.java*
3. To customize the application name, edit *AndroidManifest.xml* and replace
   `com.roccoormm.app` with an identifier for your product package.
4. To change the application name edit `<string name="app_name">SDL2 Application</string>`
   in *strings.xml*
5. To change the application icons replace the icons in
   *SDL2AppTemplate/sdl2app/src/main/res*