// Implementation file for managing visual and interactive components of the game

#include <stdbool.h>
#include <SDL2/SDL.h>

#include "manager.h"
#include "interface.h"

struct grid_square {
    SDL_Rect rect;
    Piece *piece;
};

struct game_piece {
    ;
};

/* Constants */
const int OUTER_BOARDER_WIDTH = 64;
const int INNER_BOARDER_WIDTH = 80;

Square *createBoard() {
    Square *board = malloc(sizeof(Square) * 64); // this allocates memory for an array of pointers to Squares

    for(int i = 0; i < 64; i++) {
        Square s = malloc(sizeof(&s)); // this allocates memory for individual squares
        SDL_Rect r;
        r.x = 0;
        r.y = 0;
        s->rect = r;
        board[i] = s;
    }

    return board;
}

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

void fillBoard(Square *board, SDL_Surface *surface) {
    // position of squares
    int squareXBase = (getWidth() - (getWidth() - getInnerBoarderWidth() / 2));
    int squareYBase = (getHeight() - (getHeight() - getInnerBoarderWidth() / 2));

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

    // square tracker
    int x = squareXBase;
    int y = squareYBase;

    for (int i = 1; i <= 64; i++) {
        SDL_Rect position;
        position.x = x;
        position.y = y;

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
        SDL_Surface *surf = SDL_CreateRGBSurface(0, squareWidth, squareHeight, 32, 0, 0, 0, 0);
        // adds colour to surface
        SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, squareRed, squareGreen, squareBlue));
        // blits surface in correct position
        SDL_BlitSurface(surf, NULL, surface, &position);

        // updates position width
        x += squareWidth;

        if (i % 8 == 0) {
            // upating the grid pattern
            if (i % 16 != 0) {
                colourA = 255;
                colourB = 0;
            } else {
                colourA = 0;
                colourB = 255;
            }

            // updates position height and resets width
            x = squareXBase;
            y += squareHeight;
        }
        board[i - 1]->rect.x = position.x;
        board[i - 1]->rect.y = position.y;
    }
}

void loadPieces(SDL_Surface *surface) {
    SDL_Surface *b_pawn = loadFile("images/b_pawn.png");
    SDL_Surface *w_pawn = loadFile("images/w_pawn.png");
    SDL_Surface *b_king = loadFile("images/b_king.png");
    SDL_Surface *w_king = loadFile("images/w_king.png");
    SDL_Surface *b_rook = loadFile("images/b_rook.png");
    SDL_Surface *w_rook = loadFile("images/w_rook.png");
    SDL_Surface *b_bishop = loadFile("images/b_bishop.png");
    SDL_Surface *w_bishop = loadFile("images/w_bishop.png");
    SDL_Surface *b_knight = loadFile("images/b_knight.png");
    SDL_Surface *w_knight = loadFile("images/w_knight.png");
    SDL_Surface *b_queen = loadFile("images/b_queen.png");
    SDL_Surface *w_queen = loadFile("images/w_queen.png");


    // position of squares
    int squareXBase = (getWidth() - (getWidth() - getInnerBoarderWidth() / 2));
    int squareYBase = (getHeight() - (getHeight() - getInnerBoarderWidth() / 2));
    SDL_Rect position;
    position.x = squareXBase;
    position.y = squareYBase;

    // size of squares
    int squareWidth = (getWidth() - getInnerBoarderWidth()) / 8;
    int squareHeight = (getHeight() - getInnerBoarderWidth()) / 8;

    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            switch(i) {
                case 1:
                    switch(j) {
                        case 1:
                            SDL_BlitSurface(b_rook, NULL, surface, &position);
                            break;
                        case 2:
                            SDL_BlitSurface(b_knight, NULL, surface, &position);
                            break;
                        case 3:
                            SDL_BlitSurface(b_bishop, NULL, surface, &position);
                            break;
                        case 4:
                            SDL_BlitSurface(b_queen, NULL, surface, &position);
                            break;
                        case 5:
                            SDL_BlitSurface(b_king, NULL, surface, &position);
                            break;
                        case 6:
                            SDL_BlitSurface(b_bishop, NULL, surface, &position);
                            break;
                        case 7:
                            SDL_BlitSurface(b_knight, NULL, surface, &position);
                            break;
                        case 8:
                            SDL_BlitSurface(b_rook, NULL, surface, &position);
                            break;
                    }
                    break;
                case 8:
                    switch(j) {
                        case 1:
                            SDL_BlitSurface(w_rook, NULL, surface, &position);
                            break;
                        case 2:
                            SDL_BlitSurface(w_knight, NULL, surface, &position);
                            break;
                        case 3:
                            SDL_BlitSurface(w_bishop, NULL, surface, &position);
                            break;
                        case 4:
                            SDL_BlitSurface(w_queen, NULL, surface, &position);
                            break;
                        case 5:
                            SDL_BlitSurface(w_king, NULL, surface, &position);
                            break;
                        case 6:
                            SDL_BlitSurface(w_bishop, NULL, surface, &position);
                            break;
                        case 7:
                            SDL_BlitSurface(w_knight, NULL, surface, &position);
                            break;
                        case 8:
                            SDL_BlitSurface(w_rook, NULL, surface, &position);
                            break;
                    }
                    break;
                case 2:
                    SDL_BlitSurface(b_pawn, NULL, surface, &position);
                    break;
                case 7:
                    SDL_BlitSurface(w_pawn, NULL, surface, &position);
                    break;
            }

            // SDL_BlitSurface(b_pawn, NULL, surface, &position);
            position.x += squareWidth;
        }

        position.x = squareXBase;
        position.y += squareHeight;
    }
}

void setupBoard(Square *board, SDL_Surface *surface) {
    outlineBoard(surface);
    fillBoard(board, surface);
    // loadPieces(surface);
}

void printBoard(Square *board) {
    for(int i = 0; i < 64; i++) {
        printf("Square:%d, x:%d, y:%d\n", i, board[i]->rect.x, board[i]->rect.y);
    }
}