// Implementation file for managing visual and interactive components of the game

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "manager.h"

/* Constants */
const int OUTER_BOARDER_WIDTH = 64;
const int INNER_BOARDER_WIDTH = 80;

// Surface grid for the game board
SDL_Surface *board[8][8];

void outlineBoard(SDL_Surface *surface) {
    // Sets background to white
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));

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

void loadPieces(SDL_Surface *surface) {
    SDL_Surface *temp = loadFile("images/background_test.bmp");

    int squareXBase = (getWidth() - (getWidth() - getInnerBoarderWidth() / 2));
    int squareYBase = (getHeight() - (getHeight() - getInnerBoarderWidth() / 2));
    SDL_Rect position;
    position.x = squareXBase;
    position.y = squareYBase;
    SDL_BlitSurface(temp, NULL, surface, &position);
}

void setupBoard(SDL_Surface *surface) {
    outlineBoard(surface);
    fillBoard(surface);
    loadPieces(surface);
}