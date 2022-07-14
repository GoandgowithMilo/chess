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
// Surface map for game board
SDL_Surface *board[8][8];

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
            outlineBoard();

            // Quit flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            // Event loop
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) { // quits the event loop
                        quit = true;
                    } else {
                        ;
                    }
                }

                // Coloured Square// myWindowSurface = SDL_CreateRGBSurface(0, getWidth(), getHeight(), 32, 0, 0, 0, 0);
                
                // outlineBoard();

                // fillBoard(); // This is eating all my memory and crashing the program lol

                // for (int i = 0; i < 7; i++) {
                //     for (int j = 0; j < 7; j++) { //TODO - need to do some maths here to work out correct size and positions for grid squares
                //         SDL_Rect position;
                //         position.h = getHeight()/8;
                //         position.w = getWidth()/8;
                //         position.x = getWidth()/8 * (j + 1);
                //         position.y = getHeight()/8 * (i + 1);
                //         SDL_BlitSurface(board[i][j], NULL, myWindowSurface, &position);
                //     }
                // }


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

void outlineBoard() {
    // Outer boarders
    int outerBoarders = 64;

    SDL_Surface *outer = SDL_CreateRGBSurface(0, getWidth() - outerBoarders, getHeight() - outerBoarders, 32, 0, 0, 0, 0);
    SDL_FillRect(outer, NULL, SDL_MapRGB(outer->format, 0, 0, 0));
    SDL_Rect outerPosition;
    outerPosition.x = outerBoarders/2;
    outerPosition.y = outerBoarders/2;

    SDL_BlitSurface(outer, NULL, myWindowSurface, &outerPosition);

    // Inner boarders
    int innerBoarders = 80;

    SDL_Surface *inner = SDL_CreateRGBSurface(0, getWidth() - innerBoarders, getHeight() - innerBoarders, 32, 0, 0, 0, 0);
    SDL_FillRect(inner, NULL, SDL_MapRGB(inner->format, 255, 255, 255));
    SDL_Rect innerPosition;
    innerPosition.x = innerBoarders/2;
    innerPosition.y = innerBoarders/2;

    SDL_BlitSurface(inner, NULL, myWindowSurface, &innerPosition);
}

void fillBoard() {

    int x = 255;

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            board[i][j] = SDL_CreateRGBSurface(0, getWidth()/8, getHeight()/8, 32, 0, 0, 0, 0);

            if (i % 2 == 0) {
                SDL_FillRect(board[i][j], NULL, SDL_MapRGB(board[i][j]->format, 0, 0, x));
                if (x == 255) {
                    x = 125;
                } else {
                    x = 255;
                }
            } else {
                SDL_FillRect(board[i][j], NULL, SDL_MapRGB(board[i][j]->format, 255, 0, 0));
            }
        }
    }
}