// Main file containing event loop

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "interface.h"

// Loads individual image
SDL_Surface *loadSurface(char *str);

// Fills the surfaces for the grid
void fillBoard();

// Creates an outline for the board
void outlineBoard();

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

            myWindow = createWindow(); // create the window
            myWindowSurface = getSurface(myWindow); // get the surface for that window
            SDL_FillRect(myWindowSurface, NULL, SDL_MapRGB(myWindowSurface->format, 255, 255, 255));
            outlineBoard(myWindowSurface);
            fillBoard(myWindowSurface);

            // Quit flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            /* 
                TESTING STUFF
                Need to have a load media function
                Need to remove the background from an image and workout how to do this
                work out how to use this from spritesheets

                Also need to functionize fillboard and move it elswhere
            */

            // tasks:
            // 1. how do I import an image without its background? Can bitmap images be background free? Should I import as png instead?
            // 2. how do I import images as a spritesheet and load them seperately
            // 3. function for positioning the different pieces at start of game
            // 4. fen notation for enabling different arrangement of pieces at start of game
            
            loadMedia();
            SDL_Rect scaling;
            scaling.h = 90;
            scaling.w = 90;
            SDL_BlitScaled(keyPressSurfaces[0], NULL, myWindowSurface, &scaling);



            // Event loop
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) { // quits the event loop
                        quit = true;
                    } else {
                        ;
                    }
                }

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
    keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("images/set.bmp");
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