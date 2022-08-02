// Implementation file for managing visual and interactive components of the game

#include <stdbool.h>
#include <SDL2/SDL.h>

/* Constants */
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 960;
const int OUTER_BOARDER_WIDTH = 64;
const int INNER_BOARDER_WIDTH = 80;

// Surface map for game board
SDL_Surface *board[8][8];


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


// Creates a window, returning it on succss or NULL on failure
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

// Returns the screen width
int getWidth() {
    return SCREEN_WIDTH;
}

// Returns the screen height
int getHeight() {
    return SCREEN_HEIGHT;
}

void outlineBoard(SDL_Surface *surface) {
    // Outer boarders
    SDL_Surface *outer = SDL_CreateRGBSurface(0, getWidth() - OUTER_BOARDER_WIDTH, getHeight() - OUTER_BOARDER_WIDTH, 32, 0, 0, 0, 0);
    SDL_FillRect(outer, NULL, SDL_MapRGB(outer->format, 0, 0, 0));
    SDL_Rect outerPosition;
    outerPosition.x = OUTER_BOARDER_WIDTH/2;
    outerPosition.y = OUTER_BOARDER_WIDTH/2;
    SDL_BlitSurface(outer, NULL, surface, &outerPosition);

    // Inner boarders
    SDL_Surface *inner = SDL_CreateRGBSurface(0, getWidth() - INNER_BOARDER_WIDTH, getHeight() - INNER_BOARDER_WIDTH, 32, 0, 0, 0, 0);
    SDL_FillRect(inner, NULL, SDL_MapRGB(inner->format, 255, 255, 255));
    SDL_Rect innerPosition;
    innerPosition.x = INNER_BOARDER_WIDTH/2;
    innerPosition.y = INNER_BOARDER_WIDTH/2;
    SDL_BlitSurface(inner, NULL, surface, &innerPosition);
}

int getOuterBoarderWidth() {
    return OUTER_BOARDER_WIDTH;
}

int getInnerBoarderWidth() {
    return INNER_BOARDER_WIDTH;
}

void fillBoard(SDL_Surface *surface) {
    // position of squares
    int squareXBase = (getWidth() - (getWidth() - getInnerBoarderWidth() / 2));
    int squareYBase = (getHeight() - (getHeight() - getInnerBoarderWidth() / 2));
    SDL_Rect position;
    position.x = squareXBase;
    position.y = squareYBase;

    // size of squares
    int squareWidth = (getWidth() - getInnerBoarderWidth()) / 8;
    int squareHeight = (getHeight() - getInnerBoarderWidth()) / 8;

    // colour flags
    bool colFlag = true;
    int colourA = 0;
    int colourB = 255;

    // square colour
    int squareRed = colourB;
    int squareGreen = colourB;
    int squareBlue = colourB;

    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            // updates colour
            if (colFlag) {
                squareRed = colourB;
                squareGreen = colourB;
                squareBlue = colourB;
                
                colFlag = false;
            } else {
                squareRed = colourA;
                squareGreen = colourA;
                squareBlue = colourA;

                colFlag = true;
            }

            // creates surface
            board[i][j] = SDL_CreateRGBSurface(0, squareWidth, squareHeight, 32, 0, 0, 0, 0);
            // adds colour to surface
            SDL_FillRect(board[i][j], NULL, SDL_MapRGB(board[i][j]->format, squareRed, squareGreen, squareBlue));
            // blits surface in correct position
            SDL_BlitSurface(board[i][j], NULL, surface, &position);

            // updates position width
            position.x += squareWidth;
        }

        // upating the grid pattern
        if (i % 2 != 0) {
            colourA = 255;
            colourB = 0;
        } else {
            colourA = 0;
            colourB = 255;
        }

        // updates position height and resets width
        position.x = squareXBase;
        position.y += squareHeight;
    }
}