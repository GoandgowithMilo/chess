// Main file containing event loop

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "interface.h"
#include "manager.h"

int main(int argc, char *argv[]) {
    // Window we're rendering to
    SDL_Window *myWindow = NULL;

    // The surface contained by the window
    SDL_Surface *myWindowSurface = NULL;

    // Create the game board
    Square * board = createBoard();

    if (initSDL()) {

            myWindow = createWindow(); // create the window
            SDL_Renderer *renderer = SDL_CreateRenderer(myWindow, -1, 0);
            if (renderer == NULL) {
                printf("Failed to setup renderer\n");
            }
            myWindowSurface = getSurface(myWindow); // get the surface for that window
            setupBoard(board, myWindowSurface);
            printBoard(board);

            // Quit flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            // Coordinate
            SDL_Point mousePos;

            // Event loop
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) { // quits the event loop
                        quit = true;
                    } else {
                        ;
                    }
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        mousePos.x = e.motion.x;
                        mousePos.y = e.motion.y;
                        printf("x: %d, y: %d\n", mousePos.x, mousePos.y);
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