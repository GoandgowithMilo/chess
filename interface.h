// Header file for managing visual and interactive components of the game
typedef struct game_piece *Piece;
typedef struct grid_square *Square;

// Creates the board data structure
Square *createBoard();

// Generates the outline and background for the board
void outlineBoard(SDL_Surface *surface);

// Returns the width of the outer boarder
// Note: it's square so n by n
int getOuterBoarderWidth();

// Returns the height of the inner boarder
// Note: it's square so n by n
int getInnerBoarderWidth();

// Generates the grid and outline for the game board
void fillBoard(Square *board, SDL_Surface *surface);

// // Loads all pieces onto board surface
void loadPieces(Square *board);

// Calls fillBoard, outlineBoard and loadPieces to setup the board
void setupBoard(Square *board, SDL_Surface *surface);

// Test function to print the board out
void printBoard(Square *board);

// Takes in a square, if the square contains a piece returns that piece, otherwise
// this function returns NULL
Piece containsPiece(Square square);

// Updates the visuals and data structure for the board
void updateBoard(Square *board, SDL_Surface *surface);