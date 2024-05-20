#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Animation
{
public:
    Animation(SDL_Renderer *renderer, std::string path, int x, int y, int frameWidth, int frameHeight, int frameCount, int frameRate, int perRow);
    void render(SDL_Renderer *renderer);
    SDL_Rect getRect();
    void update();

private:
    int frameCount;
    int frameRate;
    int currentFrame;
    int frameWidth;
    int frameHeight;
    int x;
    int y;
    SDL_Texture *texture;
    SDL_Rect animationRect;
    int perRow;
    int currentRow;
    int lastUpdateTime;
};

#endif