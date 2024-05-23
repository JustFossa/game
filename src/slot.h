#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Slot
{
public:
    Slot(SDL_Renderer *renderer, std::string path, float x, float y, float w, float h, int slotNumber, int frameCount);
    void render(SDL_Renderer *renderer);
    void update();

private:
    int slotNumber;
    int frameCount;
    int currentFrame;
    float x;
    float y;
    float w;
    float h;
    SDL_Texture *texture;
};