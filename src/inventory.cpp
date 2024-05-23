#include "inventory.h"
#include "utils.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>

SDL_Rect itemRect;

Inventory::Inventory(SDL_Renderer *renderer, std::string texture, int x, int y, int frameWidth, int frameHeight, int frameCount)
{
    this->x = x;
    this->renderer = renderer;
    this->y = y;
    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;
    this->frameCount = frameCount;
    this->texture = loadTexture(texture, renderer);
    this->currentFrame = 0;
    itemRect = {x, y, frameWidth * 3, frameHeight * 3};
}

void Inventory::render(SDL_Renderer *renderer)
{
    SDL_Rect srcRect = {currentFrame * frameWidth, 0, frameWidth, frameHeight};
    for (Slot *slot : slots)
    {
        slot->render(renderer);
    }
}

SDL_Rect Inventory::getRect()
{
    return itemRect;
}

void Inventory::renderItems(SDL_Renderer *renderer)
{
    for (Item *item : items)
    {
        item->render(renderer);
    }
}

void Inventory::addItem(Item *item)
{
    item->updateRect(itemRect);
    items.push_back(item);
}

void Inventory::removeItem(Item *item)
{
    return;
}

void Inventory::update()
{
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastUpdateTime > (1000 / 10)) // Update based on frameRate
    {
        currentFrame++;
        if (currentFrame >= frameCount)
        {
            currentFrame = 0; // Reset to the first frame
        }
        lastUpdateTime = currentTime;
    }
}

void Inventory::initSlots(int count)
{
    for (int i = 0; i < count; i++)
    {
        slots.push_back(new Slot(renderer, "assets/inventory.png", x + (i * frameWidth), y, frameWidth, frameHeight, i, frameCount));
    }
}