#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class HealthBar
{
public:
    HealthBar(SDL_Renderer *renderer, std::string texture, int health, int maxHealth, int x, int y, int frameWidth, int frameHeight, int frameCount);

    void render(SDL_Renderer *renderer);

    void setHealth(int health);

    int getHealth() { return health; }

private:
    int health;
    int maxHealth;
    int frameWidth, frameHeight, frameCount, frameRate, x, y;
    SDL_Texture *texture;
};

#endif // HEALTHBAR_H