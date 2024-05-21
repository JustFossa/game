#ifndef HUD_H
#define HUD_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "animation.h"
#include "healthbar.h"
#include "inventory.h"

class HUD
{
public:
    HUD(SDL_Renderer *renderer, HealthBar *healthBar, Inventory *inventory);
    void render(SDL_Renderer *renderer);
    HUD getInstance() { return *this; }
    Inventory *getInventory() { return inventory; }
    HealthBar *getHealthBar() { return healthBar; }

private:
    HealthBar *healthBar;
    Inventory *inventory;
};

#endif // HUD_H