// Header file for managing visual and interactive components of the game

// Generates the outline and background for the board
void outlineBoard(SDL_Surface *surface);

// Returns the width of the outer boarder
// Note: it's square so n by n
int getOuterBoarderWidth();

// Returns the height of the inner boarder
// Note: it's square so n by n
int getInnerBoarderWidth();

// Generates the grid and outline for the game board
void fillBoard(SDL_Surface *surface);

// Loads all pieces onto board surface
void loadPieces();

// Arranges pieces on board
void setupBoard();