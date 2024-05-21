#include "healthbar.h"
#include "utils.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>

HealthBar::HealthBar(SDL_Renderer *renderer, std::string texture, int health, int maxHealth, int x, int y, int frameWidth, int frameHeight, int frameCount)
{
    this->health = health;
    this->maxHealth = maxHealth;
    this->x = x;
    this->y = y;
    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;
    this->frameCount = frameCount;
    this->texture = loadTexture(texture, renderer);
}

void HealthBar::render(SDL_Renderer *renderer)
{
    int currentFrame = (((maxHealth - health) * frameCount) / maxHealth);
    if (currentFrame > 0)
    {
        currentFrame--;
    }
    SDL_Rect srcRect = {currentFrame * frameWidth, 0, frameWidth, frameHeight};
    SDL_Rect destRect = {x, y, frameWidth * 5, frameHeight * 5};
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}

void HealthBar::setHealth(int health)
{
    if (health >= 0 && health <= maxHealth)
    {
        this->health = health;
    }
    else if (health > maxHealth)
    {
        this->health = maxHealth;
    }
    else if (health < 0)
    {
        this->health = 0;
    }
}