// Main file containing event loop

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "interface.h"

// Loads individual image
SDL_Surface *loadSurface(char *str);

enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

/* Global Variables */
// Window we're rendering to
SDL_Window *myWindow = NULL;

// The surface contained by the window
SDL_Surface *myWindowSurface = NULL;

// Images that correspond to key press
SDL_Surface *keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

// Current image displayed
SDL_Surface *currentSurface = NULL;

// The image we'll load and show on the screen
// SDL_Surface *myMedia = NULL; // SDL_Surface is just an image datatype that contains the pixels of an image + the data to render it correctly --> uses software rendering so CPU

int main(int argc, char *argv[]) {
    if (initVideo()) {

            myWindow = createWindow();
            myWindowSurface = getSurface(myWindow);


            if (loadMedia()) {
                ;
                // SDL_BlitSurface(currentSurface, NULL, myWindowSurface, NULL);
            } else {
                printf("Failed to load media!\n");
            }

            // Quit flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            // Set default current surface
            currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

            // Event loop
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {
                        if (e.key.keysym.sym == SDLK_q) {
                            currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                        } else {
                            currentSurface = keyPressSurfaces[KEY_PRESS_SURFACE_UP]; // all the others are the same
                        }
                    }
                }

                // Stretch and blit image
                SDL_Rect resize;
                resize.x = 0;
                resize.y = 0;
                resize.w = getWidth();
                resize.h = getHeight();
                SDL_BlitScaled(currentSurface, NULL, myWindowSurface, &resize);

                // Update surface
                SDL_UpdateWindowSurface(myWindow);
            }

    } else {
        printf("Failure to initialize\n");
    }

    // closes SDL
    closeSDL(myWindow, myWindowSurface);

    return 0;
}

bool loadMedia() {
    // Loading media flag
    bool success = true;

    // Load default surface
    keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("images/test1.bmp");
    if (keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
        printf("Failed to load default image!\n");
        success = false;
    }

    // Load other surfaces
    keyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("images/test2.bmp");
    if (keyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
        printf("Failed to load up image!\n");
        success = false;
    }

    keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("images/test2.bmp");
    if (keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
        printf("Failed to load down image!\n");
        success = false;
    }
    
    keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("images/test2.bmp");
    if (keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
        printf("Failed to load left image!\n");
        success = false;
    }
    
    keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("images/test2.bmp");
    if (keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
        printf("Failed to load right image!\n");
        success = false;
    }

    return success;
}

SDL_Surface *loadSurface(char *str) {
    // Optimized image format
    SDL_Surface *optimizedSurface = NULL;

    // Loads an image at the specified file path
    SDL_Surface *loadedSurface = SDL_LoadBMP(str);

    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", str, SDL_GetError());
    } else {
        // Convert to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, myWindowSurface->format, 0);
        if (optimizedSurface == NULL) {
            printf("Unable to optimize image %s! SDL Error: %s\n", str, SDL_GetError());
        }

        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}