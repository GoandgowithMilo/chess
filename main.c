#include <stdio.h>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[]) {
    // window we're rendering to
    SDL_Window *window = NULL;

    // the surface contained by the window
    SDL_Surface *surface = NULL;

    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL! Error: %s\n", SDL_GetError());
    } else {
        // create a window
        window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (window == NULL) {
            printf("Window could not be created! Error: %s\n", SDL_GetError());
        } else {
            // get the window surface 
            surface = SDL_GetWindowSurface(window);

            /* MY CODE */
            SDL_Rect rect;
            rect.h = 50;
            rect.w = 50;
            rect.x = 0;
            rect.y = 0;

            // fill the surface with white
            SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0, 0, 0xFF));

            // update the window
            SDL_UpdateWindowSurface(window);

            // delay to delete
            SDL_Delay(2000);
        }
    }


    return 0;
}