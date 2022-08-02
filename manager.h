// Header file for components related to managing and using SDL

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

// Loads bitmap at the specified file path to the current location
SDL_Surface *loadSurface(char *str);

// Returns the screen width
int getWidth();

// Returns the screen height
int getHeight();
