#include "utils.h"
#include <SDL_image.h>
#include <stdio.h>

SDL_Surface *loadSurface(std::string path, SDL_Window *window)
{
    SDL_Surface *optimizedSurface = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
        optimizedSurface = SDL_ConvertSurface(loadedSurface, SDL_GetWindowSurface(window)->format, 0);
        if (optimizedSurface == NULL)
        {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

SDL_Texture *loadTexture(std::string path, SDL_Renderer *renderer)
{
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}
