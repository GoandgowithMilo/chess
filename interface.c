// Implementation file for managing visual and interactive components of the game

#include <stdbool.h>
#include <SDL2/SDL.h>

#include "manager.h"
#include "interface.h"

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
        board[i - 1]->sqr = surf;
    }
}


// update this function to take in the board, iterate through it and place pieces in their correct
// initial positions as elements of the squares
void loadPieces(Square *board) {
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

    for (int i = 0; i < 64; i++) {
        if ((i == 0) || (i == 7)) {
            Piece p = malloc(sizeof(&p)); // allocate memory for the piece
            p->image = b_rook;
            p->team = 0;
            p->value = 1;
            board[i]->piece = p;       
        } else 
        if ((i == 1) || (i == 6)) {
            Piece p = malloc(sizeof(&p)); // allocate memory for the piece
            p->image = b_knight;
            p->team = 0;
            p->value = 2;
            board[i]->piece = p;       
        } else
        if ((i == 2) || (i == 5)) {
            Piece p = malloc(sizeof(&p)); // allocate memory for the piece
            p->image = b_bishop;
            p->team = 0;
            p->value = 3;
            board[i]->piece = p;       
        } else
        if (i == 3) {
            Piece p = malloc(sizeof(&p)); // allocate memory for the piece
            p->image = b_queen;
            p->team = 0;
            p->value = 4;
            board[i]->piece = p;       
        } else
        if (i == 4) {
            Piece p = malloc(sizeof(&p)); // allocate memory for the piece
            p->image = b_king;
            p->team = 0;
            p->value = 5;
            board[i]->piece = p;       
        } else 
        if ((i > 7) && (i < 16)) {
            Piece p = malloc(sizeof(&p)); // allocate memory for the piece
            p->image = b_pawn;
            p->team = 0;
            p->value = 0;
            board[i]->piece = p;       
        } else 
        if ((i > 47) && (i < 56)) {
            Piece p = malloc(sizeof(&p)); // allocate memory for the piece
            p->image = w_pawn;
            p->team = 1;
            p->value = 0;
            board[i]->piece = p;
        } else
        if ((i == 56) || (i == 63)) {
            Piece p = malloc(sizeof(&p)); // allocate memory for the piece
            p->image = w_rook;
            p->team = 1;
            p->value = 1;
            board[i]->piece = p;
        } else
        if ((i == 57) || (i == 62)) {
            Piece p = malloc(sizeof(&p)); // allocate memory for the piece
            p->image = w_knight;
            p->team = 1;
            p->value = 2;
            board[i]->piece = p;
        } else
        if ((i == 58) || (i == 61)) {
            Piece p = malloc(sizeof(&p)); // allocate memory for the piece
            p->image = w_bishop;
            p->team = 1;
            p->value = 3;
            board[i]->piece = p;
        } else 
        if (i == 59) {
            Piece p = malloc(sizeof(&p)); // allocate memory for the piece
            p->image = w_queen;
            p->team = 1;
            p->value = 4;
            board[i]->piece = p;
        } else
        if (i == 60) {
            Piece p = malloc(sizeof(&p)); // allocate memory for the piece
            p->image = w_king;
            p->team = 1;
            p->value = 5;
            board[i]->piece = p;
        }
    }
}

void setupBoard(Square *board, SDL_Surface *surface) {
    outlineBoard(surface);
    fillBoard(board, surface);
    loadPieces(board);
}

void printBoard(Square *board) {
    for(int i = 0; i < 64; i++) {
        printf("Square:%d, x:%d, y:%d ", i, board[i]->rect.x, board[i]->rect.y);
        if(containsPiece(board[i]) == NULL) {
            printf("Does not contain piece!\n");
        } else {
            printf("Piece: %d\n", board[i]->piece->value);
        }
    }
}

Piece containsPiece(Square square) {
    return square->piece;
}

void updateBoard(Square *board, SDL_Surface *surface) {
    for (int i = 0; i < 64; i++) {
        if (containsPiece(board[i]) != NULL) {
            SDL_BlitSurface(board[i]->sqr, NULL, surface, &board[i]->rect);
            SDL_BlitSurface(board[i]->piece->image, NULL, surface, &board[i]->rect);
        } else {
            SDL_BlitSurface(board[i]->sqr, NULL, surface, &board[i]->rect);
        }
    }
}

int selectedSquare(SDL_Point p) {
    int result = -1;

    int mouse_x = p.x;
    int mouse_y = p.y;
    int x = 0;
    int y = 0;

    if ((mouse_x > 40) && (mouse_x < 920)) { // check we're in x bounds
        if ((mouse_y > 40) && (mouse_y < 920)) { // check we're in y bounds
            x = (mouse_x - 40) / 110;
            y = (mouse_y - 40) / 110;

            result = (x + y * 8);
        }
    }

    return result;
}