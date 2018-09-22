#include "SDL.h"
#include <SDL_opengles.h>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_GL_LoadLibrary(NULL);
    SDL_Window *window = SDL_CreateWindow(
            "An SDL2 window",                  // window title
            SDL_WINDOWPOS_UNDEFINED,           // initial x position
            SDL_WINDOWPOS_UNDEFINED,           // initial y position
            640,                               // width, in pixels
            480,                               // height, in pixels
            SDL_WINDOW_OPENGL                  // flags - see below
    );
    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        SDL_Log("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GLContext glContext = nullptr;
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
#if defined(__ANDROID__ )
    const auto GL_ContextProfile = SDL_GL_CONTEXT_PROFILE_ES;
#else
    const auto GL_ContextProfile = SDL_GL_CONTEXT_PROFILE_CORE;
#endif
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, GL_ContextProfile);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    const int GL_MajorVersion = 4;
    const int GL_MinorVersion = 9;
    for (int majorVersion = GL_MajorVersion; 3 <= majorVersion; --majorVersion) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, majorVersion);
        // Search for the highest possible context version
        for (int minorVersion = GL_MinorVersion; 0 <= minorVersion; --minorVersion) {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorVersion);
            glContext = SDL_GL_CreateContext(window);
            if (nullptr == glContext) {
                continue;
            }
            break;
        }
    }
    if (nullptr == glContext) {
        SDL_Log("Unable to create OpenGL context: %s", SDL_GetError());
        return -1;
    }

    bool isRunning = true;
    bool isQuitting = false;

    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    // Event handler
    SDL_Event e;
    // While application is running
    while (isRunning) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                isQuitting = true;
            }
            if (e.type == SDL_MULTIGESTURE) {
                if (e.mgesture.numFingers == 2) {
                    isQuitting = true;
                }
                if (e.mgesture.numFingers == 3) {
                    if (isQuitting) {
                        isRunning = false;
                    }
                }
                if (e.mgesture.numFingers > 3) {
                    isQuitting = false;
                }

            }
        }

        r = (1.0f < r) ? (0.0f) : (r + 0.01f);
        g = (1.0f < g) ? (0.0f) : (g + 0.02f);
        b = (1.0f < b) ? (0.0f) : (b + 0.03f);

        glClearColor(r, g, b, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glContext);

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();

    return 0;
}
