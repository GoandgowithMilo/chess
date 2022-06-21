#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

/* Helper Functions */
// Initializes SDL, returning true on success or false on failure
bool initSDL();

// Loads media, returning true on success or false on failure
bool loadMedia();

// Frees media and shutdowns SDL
void closeSDL();

/* Constants */
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/* Global Variables */
// Window we're rendering to
SDL_Window *myWindow = NULL;

// The surface contained by the window
SDL_Surface *myWindowSurface = NULL;

// The image we'll load and show on the screen
SDL_Surface *myMedia = NULL; // SDL_Surface is just an image datatype that contains the pixels of an image + the data to render it correctly --> uses software rendering so CPU

int main(int argc, char *argv[]) {
    if (initSDL()) {

            /* MY CODE */
            SDL_Rect rect;
            rect.h = 50;
            rect.w = 50;
            rect.x = 0;
            rect.y = 0;

            // fill the surface with blue
            SDL_FillRect(myWindowSurface, &rect, SDL_MapRGB(myWindowSurface->format, 0, 0, 0xFF));

            // update the window
            SDL_UpdateWindowSurface(myWindow);

            // delay to delete
            SDL_Delay(2000);
    }

    return 0;
}

bool initSDL() {
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL failed to initialize with error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Create window
        myWindow = SDL_CreateWindow("Chess: Alpha", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (myWindow == NULL) {
            printf("myWindow failed to initialize: %s\n", SDL_GetError());
            success = false;
        } else {
            // Get window surface
            myWindowSurface = SDL_GetWindowSurface(myWindow);
        }
    }

    return success;
}