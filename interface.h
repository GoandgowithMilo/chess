// Header file for managing visual and interactive components of the game

// Initializes SDL_VIDEO, returning true on success or false on failure
bool initVideo();

// Creates a window, returning it on succss or NULL on failure
SDL_Window *createWindow();

// Gets a surface from a window, returning it on success or NULL on failure
SDL_Surface *getSurface(SDL_Window *window);

// Frees media and shutdowns SDL
void closeSDL(SDL_Window *window, SDL_Surface *surface);

// Loads media, returning true on success or false on failure
bool loadMedia();

// Returns the screen width
int getWidth();

// Returns the screen height
int getHeight();

// Generates the outline and background for the board
void outlineBoard(SDL_Surface *surface);

// Returns the width of the outer boarder
// Note: it's square so n by n
int getOuterBoarderWidth();

// Returns the height of the inner boarder
// Note: it's square so n by n
int getInnerBoarderWidth();