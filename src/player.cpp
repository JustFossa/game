#include "player.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>
#include "map.h"
#include <math.h>
#include "utils.h"
#include <vector>
#include "healthbar.h"

const float JUMP_DELAY = 1000;
const float JUMP_HEIGHT = 50;
const float JUMP_SPEED = 20.0f;
const float GRAVITY = 1.0f;
static bool jumping = false;

Player::Player(SDL_Renderer *renderer, std::string path, float x, float y, float w, float h, float speed, HealthBar *healthBar)
{
    this->playerRect = {static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h)};
    this->speed = speed;
    this->texture = loadTexture(path, renderer);
    this->healthBar = healthBar;
}

void Player::render(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, &playerRect);
}

void Player::move(Map *map)
{
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    float newX = playerRect.x;
    float newY = playerRect.y;

    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        newX -= speed;
    }
    if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        newX += speed;
    }
    if (currentKeyStates[SDL_SCANCODE_UP])
    {
        newY -= speed;
    }
    if (currentKeyStates[SDL_SCANCODE_DOWN])
    {
        newY += speed;
    }

    newX = std::max(0.0f, std::min(newX, static_cast<float>(map->w - playerRect.w)));
    newY = std::max(0.0f, std::min(newY, static_cast<float>(map->h - playerRect.h)));

    SDL_Rect potentialRect = {static_cast<int>(newX), static_cast<int>(newY), playerRect.w, playerRect.h};
    checkCollisionWithMap(map, potentialRect);
    checkCollisionWithItems(map);

    playerRect.x = potentialRect.x;
    playerRect.y = potentialRect.y;
}

void Player::checkCollisionWithMap(Map *map, SDL_Rect &potentialRect)
{
    for (auto &rect : map->getCollisionRects())
    {
        checkCollision(rect, potentialRect);
    }
}

void Player::checkCollision(SDL_Rect &obstacle, SDL_Rect &potentialRect)
{
    int left1 = potentialRect.x;
    int right1 = potentialRect.x + potentialRect.w;
    int top1 = potentialRect.y;
    int bottom1 = potentialRect.y + potentialRect.h;

    int left2 = obstacle.x;
    int right2 = obstacle.x + obstacle.w;
    int top2 = obstacle.y;
    int bottom2 = obstacle.y + obstacle.h;

    if (bottom1 <= top2 || top1 >= bottom2 || right1 <= left2 || left1 >= right2)
    {
        return;
    }

    float overlapLeft = right1 - left2;
    float overlapRight = right2 - left1;
    float overlapTop = bottom1 - top2;
    float overlapBottom = bottom2 - top1;

    bool fromLeft = overlapLeft < overlapRight;
    bool fromTop = overlapTop < overlapBottom;

    float minOverlapX = fromLeft ? overlapLeft : overlapRight;
    float minOverlapY = fromTop ? overlapTop : overlapBottom;

    if (minOverlapX < minOverlapY)
    {
        if (fromLeft)
        {
            potentialRect.x -= minOverlapX;
        }
        else
        {
            potentialRect.x += minOverlapX;
        }
    }
    else
    {
        if (fromTop)
        {
            potentialRect.y -= minOverlapY;
        }
        else
        {
            potentialRect.y += minOverlapY;
        }
    }
}

void Player::addItem(Item *item)
{
    playerItems.push_back(item);
}

std::vector<Item *> Player::getItems()
{
    return playerItems;
}

void Player::checkCollisionWithItems(Map *map)
{
    for (auto it = map->items.begin(); it != map->items.end();)
    {
        SDL_Rect itemRect = (*it)->getRect();
        if (itemRect.x < playerRect.x + playerRect.w &&
            itemRect.x + itemRect.w > playerRect.x &&
            itemRect.y < playerRect.y + playerRect.h &&
            itemRect.y + itemRect.h > playerRect.y)
        {
            Player::addItem(*it);
            it = map->items.erase(it);
        }
        else
        {
            ++it;
        }
    }
}