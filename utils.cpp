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

SDL_Texture *renderText(SDL_Renderer *renderer, const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Rect *textRect)
{
    TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (!font)
    {
        printf("Failed to load font: %s\n", TTF_GetError());
        return nullptr;
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, message.c_str(), color);
    if (!surface)
    {
        printf("Failed to create surface: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        printf("Failed to create texture: %s\n", SDL_GetError());
    }
    else
    {
        textRect->w = surface->w;
        textRect->h = surface->h;
    }

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);

    return texture;
}