// Implementation file for components related to managing and using SDL

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "manager.h"

/* Constants */
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 960;

bool initVideo() {
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL failed to initialize with error: %s\n", SDL_GetError());
        success = false;
    } 

    return success;
}

bool initPNG() {
    bool success = true;
    int flag = IMG_INIT_PNG;

    if (!(IMG_Init(flag) & flag)) {
        printf("SDL image could not initialize! SDL image error: %s\n", IMG_GetError());
        success = false;
    }

    return success;
}

bool initSDL() {
    if(initVideo() & initPNG()) {
        return true;
    } else {
        return false;
    }
}

SDL_Window *createWindow() {
    SDL_Window *window = NULL;

    // // Get current display information
    // SDL_DisplayMode current;
    // SDL_GetCurrentDisplayMode(0, &current); // we're using 0 as index here as we have only 1 display - does not handle multiple displays but easy fix

    // Create window
    window = SDL_CreateWindow("Chess: Alpha", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window failed to initialize: %s\n", SDL_GetError());
    }

    return window;

}

// Gets a surface from a window, returning it on success or NULL on failure
SDL_Surface *getSurface(SDL_Window *window) {
    SDL_Surface *surface = NULL;

    // Get window surface
    surface = SDL_GetWindowSurface(window);
    if (surface == NULL) {
        printf("Surface failed to initialize: %s\n", SDL_GetError());
    }

    return surface;
}

void closeSDL(SDL_Window *window, SDL_Surface *surface) {
    // Deallocate the surface
    SDL_FreeSurface(surface);

    // Destroy the window
    SDL_DestroyWindow(window);

    // Quit SDL Subsystems
    SDL_Quit();
}

SDL_Surface *loadFile(char *str) {
    // // Optimized image format
    // SDL_Surface *optimizedSurface = NULL;

    // // Loads an image at the specified file path
    SDL_Surface *loadedSurface = IMG_Load(str);

    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", str, SDL_GetError());
    } else {
        // Convert to screen format
        // optimizedSurface = SDL_ConvertSurface(loadedSurface, SDL_Surface->format, 0);
        // if (optimizedSurface == NULL) {
        //     printf("Unable to optimize image %s! SDL Error: %s\n", str, SDL_GetError());
        // }

        // SDL_FreeSurface(loadedSurface);
    }

    return loadedSurface;
}

// Returns the screen width
int getWidth() {
    return SCREEN_WIDTH;
}

// Returns the screen height
int getHeight() {
    return SCREEN_HEIGHT;
}