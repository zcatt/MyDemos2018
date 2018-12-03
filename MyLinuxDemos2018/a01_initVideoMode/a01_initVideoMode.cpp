#include <SDL.h>
#include <stdlib.h>
int main()
{
    SDL_Surface *screen;
    Uint32 color;
    int x;
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        fprintf(stderr, "cannot init SDL");
        exit(1);
    }
    screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);
    if(screen == NULL)
    {
        fprintf(stderr, "cannot set video mode ");
        exit(1);
    }

    atexit(SDL_Quit);

    for(x = 0; x<=255; x++)
    {
        color = SDL_MapRGB(screen->format, 255, x,x);
        SDL_FillRect(screen, NULL, color);
        SDL_UpdateRect(screen, 0,0,0,0);
        SDL_Delay(5);
    }
    SDL_Delay(3000);
    return 0;
}