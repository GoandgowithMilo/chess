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
            myWindowSurface = getSurface(myWindow); // get the surface for that window
            setupBoard(board, myWindowSurface);

            // Quit flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            // Clicking variables
            SDL_Point mousePos;
            bool leftMouseButtonDown = false;
            Square currSqr = NULL;
            SDL_Point currentSqrPos;

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
                            }
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if ((!leftMouseButtonDown) && (e.button.button == SDL_BUTTON_LEFT) && (currSqr == NULL)) {
                                leftMouseButtonDown = true;
                                if ((selectedSquare(mousePos) != -1) && (containsPiece(board[selectedSquare(mousePos)]) != NULL)) {
                                    currSqr = board[selectedSquare(mousePos)];
                                    currentSqrPos = mousePos;
                                }
                            } else if ((!leftMouseButtonDown) && (e.button.button == SDL_BUTTON_LEFT)) {
                                // printf("Selected Square: %d, New Square: %d\n", selectedSquare(currentSqrPos), selectedSquare(mousePos));
                                if ((selectedSquare(mousePos) != selectedSquare(currentSqrPos)) && (containsPiece(board[selectedSquare(mousePos)]) == NULL)) {
                                    printf("THIS RAN\n");
                                    board[selectedSquare(mousePos)]->piece = currSqr->piece;
                                    currSqr->piece = NULL;
                                    // board[selectedSquare(mousePos)]->rect = currSqr->rect;
                                    // board[selectedSquare(mousePos)]->
                                    // SDL_BlitSurface(currSqr->piece->image, NULL, myWindowSurface, &board[selectedSquare(mousePos)]->rect);
                                }
                                currSqr = NULL;
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