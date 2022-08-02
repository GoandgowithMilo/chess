// Main file containing event loop

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "interface.h"
#include "manager.h"

// Fills the surfaces for the grid
void fillBoard();

// Creates an outline for the board
void outlineBoard();

/* Global Variables */
// Window we're rendering to
SDL_Window *myWindow = NULL;

// The surface contained by the window
SDL_Surface *myWindowSurface = NULL;

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
            
            // loadMedia();
            // SDL_Rect scaling;
            // scaling.h = 90;
            // scaling.w = 90;
            // SDL_BlitScaled(keyPressSurfaces[0], NULL, myWindowSurface, &scaling);



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