#include "player.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>
#include "map.h"
#include <math.h>
#include "utils.h"

const float JUMP_DELAY = 1000;
const float JUMP_HEIGHT = 50;
const float JUMP_SPEED = 20.0f;
const float GRAVITY = 1.0f;
static bool jumping = false;

Player::Player(SDL_Renderer *renderer, std::string path, float x, float y, float w, float h, float speed)
{
    this->playerRect = {static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h)};
    this->speed = speed;
    this->texture = loadTexture(path, renderer);
}

void Player::render(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, &playerRect);
}

void Player::move(Map *map)
{
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        if (this->playerRect.x > 0)
        {
            this->playerRect.x -= speed;
        }
    }
    if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        if (this->playerRect.x < map->w - this->playerRect.w)
        {
            this->playerRect.x += speed;
        }
    }
}

void Player::gravity(Map *map)
{
    if (this->playerRect.y < map->h - this->playerRect.h && !jumping)
    {
        this->playerRect.y += GRAVITY;
    }
}

void Player::jump(Map *map)
{
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    static bool jumping = false;
    static float jumpStart = 0;
    static float jumpHeight = 0; // Added jumpHeight variable

    if (currentKeyStates[SDL_SCANCODE_UP] && !jumping)
    {
        jumpStart = SDL_GetTicks64();
        jumping = true;
    }
    if (jumping)
    {
        float jumpTime = SDL_GetTicks64() - jumpStart;
        if (jumpTime < JUMP_DELAY)
        {
            float progress = jumpTime / JUMP_DELAY;
            float heightFactor = sqrt(progress); // Square root function for slowing down over time
            float jumpIncrement = JUMP_SPEED * heightFactor;
            if (jumpHeight + jumpIncrement <= JUMP_HEIGHT) // Check if the jump height is within the limit
            {
                this->playerRect.y -= jumpIncrement;
                jumpHeight += jumpIncrement;
                this->playerRect.y += GRAVITY / JUMP_DELAY;
            }
            else
            {
                jumping = false;
                jumpStart = 0;
                jumpHeight = 0; // Reset jumpHeight when the jump is finished
            }
        }
        else
        {
            jumping = false;
            jumpStart = 0;
            jumpHeight = 0; // Reset jumpHeight when the jump is finished
        }
    }
}
