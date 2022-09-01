// Main file containing event loop

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "interface.h"
#include "manager.h"
// #include "interface.c"

int main(int argc, char *argv[]) {
    // Window we're rendering to
    SDL_Window *myWindow = NULL;

    // The surface contained by the window
    SDL_Surface *myWindowSurface = NULL;

    // Create the game board
    Square * board = createBoard();

    if (initSDL()) {
            myWindow = createWindow(); // create the window
            // SDL_Renderer *renderer = SDL_CreateRenderer(myWindow, -1, 0);
            // if (renderer == NULL) {
            //     printf("Failed to setup renderer\n");
            // }
            myWindowSurface = getSurface(myWindow); // get the surface for that window
            setupBoard(board, myWindowSurface);
            // printBoard(board);

            // Quit flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            // Clicking variables
            SDL_Point mousePos;
            bool leftMouseButtonDown = false;
            Square currSqr = NULL;

            // Event loop
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    switch(e.type) {
                        case SDL_QUIT:
                            quit = true;
                            break;
                        case SDL_MOUSEMOTION:
                            mousePos.x = e.motion.x;
                            mousePos.y = e.motion.y;
                            break;
                        case SDL_MOUSEBUTTONUP:
                            if (leftMouseButtonDown && (e.button.button == SDL_BUTTON_LEFT)) {
                                leftMouseButtonDown = false; 
                                currSqr = NULL;
                                printf("\nSET NULL\n");
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if ((!leftMouseButtonDown) && (e.button.button == SDL_BUTTON_LEFT)) {
                                leftMouseButtonDown = true;
                                currSqr = board[selectedSquare(mousePos)];
                            }
                            break;
                    }
                }

                if ((currSqr != NULL) && (selectedSquare(mousePos) != -1) && (containsPiece(currSqr) != NULL)) {
                    // creates surface
                    SDL_Surface *surf = SDL_CreateRGBSurface(0, 110, 110, 32, 0, 0, 0, 0);
                    // adds colour to surface
                    SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 31, 255, 15));
                    // blits surface in correct position
                    SDL_BlitSurface(surf, NULL, myWindowSurface, &currSqr->rect);
                    SDL_BlitSurface(currSqr->piece->image, NULL, myWindowSurface, &currSqr->rect);
                } else {
                    updateBoard(board, myWindowSurface);
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