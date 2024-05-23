#include "slot.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "utils.h"

Slot::Slot(SDL_Renderer *renderer, std::string path, float x, float y, float w, float h, int slotNumber, int frameCount)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->slotNumber = slotNumber;
    this->frameCount = frameCount;
    this->currentFrame = 0;
    this->texture = loadTexture(path, renderer);
}

void Slot::render(SDL_Renderer *renderer)
{
    SDL_Rect srcRect = {currentFrame * w, 0, w, h};
    SDL_Rect destRect = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}

void Slot::update()
{
    currentFrame++;
    if (currentFrame >= frameCount)
    {
        currentFrame = 0;
    }
}