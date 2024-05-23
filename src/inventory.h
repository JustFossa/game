#ifndef INVETORY_H
#define INVETORY_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "animation.h"
#include "item.h"
#include <vector>
#include "slot.h"

class Inventory
{
public:
    Inventory(SDL_Renderer *renderer, std::string texture, int x, int y, int frameWidth, int frameHeight, int frameCount);
    void render(SDL_Renderer *renderer);
    SDL_Rect getRect();
    void addItem(Item *item);
    void removeItem(Item *item);
    Item *getItem(int index);
    void update();
    void renderItems(SDL_Renderer *renderer);
    std::vector<Slot *> getSlots() { return slots; };
    void initSlots(int count);

private:
    int frameCount;
    int lastUpdateTime;
    int currentFrame;
    int frameWidth;
    int frameHeight;
    int x;
    int y;
    std::vector<Slot *> slots;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    SDL_Rect animationRect;
    std::vector<Item *> items;
};

#endif // INVETORY_H