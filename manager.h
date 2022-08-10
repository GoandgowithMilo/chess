// Header file for components related to managing and using SDL

// Initializes SDL_VIDEO, returning true on success or false on failure
bool initVideo();

// Initializes PNG loading, returning true on success or false on failure
bool initPNG();

// Calls initialization functions for SDL
bool initSDL();

// Creates a window, returning it on succss or NULL on failure
SDL_Window *createWindow();

// Gets a surface from a window, returning it on success or NULL on failure
SDL_Surface *getSurface(SDL_Window *window);

// Frees media and shutdowns SDL
void closeSDL(SDL_Window *window, SDL_Surface *surface);

// Loads a png file and returns it as an SDL_Surface
SDL_Surface *loadFile(char *str);

// Returns the screen width
int getWidth();

// Returns the screen height
int getHeight();
