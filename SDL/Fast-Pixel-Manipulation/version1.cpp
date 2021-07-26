#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "benchmark.h"

/*------------ Results -----------------
    Gives 12-13ms
*/

namespace SDL
{
    SDL_DisplayMode dm;

    SDL_Window *win = nullptr;
    SDL_Surface *wsurface = nullptr;

    void init()
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_GetCurrentDisplayMode(0, &dm);
        win = SDL_CreateWindow("Default", 0, 0, dm.w, dm.h, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
        wsurface = SDL_GetWindowSurface(win);
    }

    void exit()
    {
        SDL_DestroyWindow(win);
        win = nullptr;
        SDL_Quit();
        IMG_Quit();
    }

    void run()
    {
        Uint32* pixels = static_cast<Uint32*>(wsurface->pixels);
        for(int i = 0; i < dm.w*dm.h; ++i)
        {
            pixels[i] = SDL_MapRGBA(wsurface->format, (i*23)%256, (i*51)%256, (i*71)%256, 255); // random values
        }
        SDL_UpdateWindowSurface(win);
    }
};

int main(int argc, char **argv)
{
    SDL_Event event;

    SDL::init();

    benchmark(100, SDL::run); // run it 100 times.

    while (1)
    {
        while ((SDL_PollEvent(&event) != 0))
        {
            if (event.type == SDL_QUIT)
            {
                SDL::exit();
                return 0;
            }
        }
        SDL_Delay(50);
    }
    return 0;
}