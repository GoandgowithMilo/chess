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
            printBoard(board);

            // Quit flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            // Clicking variables
            SDL_Point mousePos;
            // bool leftMouseButtonDown = false;
            // SDL_Rect *selectedRect = NULL;

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
                            printf("Square: %d\n", selectedSquare(mousePos));
                            break;
                    //     case SDL_MOUSEBUTTONUP:
                    //         if (leftMouseButtonDown && (e.button.button == SDL_BUTTON_LEFT)) {
                    //             leftMouseButtonDown = false; 
                    //             selectedRect = NULL;
                    //         }
                    //         break;
                    //     case SDL_MOUSEBUTTONDOWN:
                    //         if ((!leftMouseButtonDown) && (e.button.button == SDL_BUTTON_LEFT)) {
                    //             leftMouseButtonDown = true;
                    //             selectedRect = &board[selectedSquare(mousePos)]->rect;
                    //         }
                    //         break;
                    }
                }

                // Updates the buffer and data structure
                updateBoard(board, myWindowSurface);

                // // Highlights selected rectangle
                // SDL_FillRect(myWindowSurface, selectedRect, SDL_MapRGB(myWindowSurface->format, 255, 255, 255));
                // SDL_BlitSurface(myWindowSurface, NULL, myWindowSurface, selectedRect);


                // SDL_Surface *inner = SDL_CreateRGBSurface(0, getWidth() - INNER_BOARDER_WIDTH, getHeight() - INNER_BOARDER_WIDTH, 32, 0, 0, 0, 0);
                // SDL_FillRect(inner, NULL, SDL_MapRGB(inner->format, 255, 255, 255));
                // SDL_Rect innerPosition;
                // innerPosition.x = INNER_BOARDER_WIDTH/2;
                // innerPosition.y = INNER_BOARDER_WIDTH/2;
                // SDL_BlitSurface(inner, NULL, surface, &innerPosition);



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