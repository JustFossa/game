#include "hud.h"
#include "utils.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "healthbar.h"
#include "animation.h"
#include "inventory.h"

HUD::HUD(SDL_Renderer *renderer, HealthBar *healthBar, Inventory *inventory)
{
    this->healthBar = healthBar;
    this->inventory = inventory;
}

void HUD::render(SDL_Renderer *renderer)
{
    healthBar->render(renderer);
    inventory->render(renderer);
}