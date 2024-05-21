#include "animation.h"
#include "utils.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

Animation::Animation(SDL_Renderer *renderer, std::string path, int x, int y, int frameWidth, int frameHeight, int frameCount, int frameRate, int perRow)
{
    this->x = x;
    this->y = y;
    this->frameCount = frameCount;
    this->frameRate = frameRate;
    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;
    this->texture = loadTexture(path, renderer);
    this->animationRect = {x, y, frameWidth, frameHeight};
    this->currentFrame = 0;
    this->perRow = perRow;
    this->lastUpdateTime = SDL_GetTicks64(); // Initialize lastUpdateTime
}

void Animation::render(SDL_Renderer *renderer)
{
    int column = currentFrame % perRow;
    int row = currentFrame / perRow;
    SDL_Rect currentFrameRect = {column * frameWidth, row * frameHeight, frameWidth, frameHeight};
    SDL_Rect animationRect = {x, y, frameWidth, frameHeight};
    SDL_RenderCopy(renderer, texture, &currentFrameRect, &animationRect);
}

SDL_Rect Animation::getRect()
{
    return animationRect;
}

void Animation::update()
{
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastUpdateTime > (1000 / frameRate)) // Update based on frameRate
    {
        currentFrame++;
        if (currentFrame >= frameCount)
        {
            currentFrame = 0; // Reset to the first frame
        }
        lastUpdateTime = currentTime;
    }
}
