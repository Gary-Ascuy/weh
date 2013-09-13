
#include "gui/GUICharacter.h"

GUICharacter::GUICharacter()
{
    //ctor
}

int findex = 0;
int flag_index = 0;
int select_index = 0;
int sselect_index = 0;
Uint32 findex_tick = 0;
bool moveX = false;
bool moveY = false;

void GUICharacter::Render(SDL_Rect& viewport, ResourceManager& rm) {
    int size = 1*32;
    SDL_Rect sdst = { viewport.x + src.x - size/2, viewport.y - size + src.y, size, size};
    SpriteID id = { 0, 0, 0 };
    SpriteID boxId = { 7, 0, 0 };
    SpriteID selectId = { 9, 0, 0 };

    if (++select_index % 3 == 0) {
        sselect_index++;
    }
    selectId.row = (sselect_index) % 10;

    int dx = src.x - dst.x;
    int dy = src.y - dst.y;

    SDL_Rect sdstf = { src.x + viewport.x - 25, viewport.y + src.y - 30, 50, 50};
    rm.RenderCharacter(&sdstf, selectId);

    Uint32 aux = SDL_GetTicks();
    if (aux - findex_tick > 35) {
        findex++;
        findex_tick = aux;

        if (abs(dx) > 10) {
            if (dx > 0) src.x -= 5;
            else src.x += 5;
            moveX = true;
        } else moveX = false;

        if (abs(dy) > 10) {
            if (dy > 0) src.y -= 5;
            else src.y += 5;
            moveY = true;
        } else moveY = false;

        if (moveX || moveY) {
            id.col = findex % 4;
        }
    }

    if (abs(dx) > abs(dy)) {
        if (dx > 0) id.row = 1;
        else id.row = 2;
    } else {
        if (dy > 0) id.row = 3;
        else id.row = 0;
    }
    rm.RenderCharacter(&sdst, id);

    if (moveX || moveY) {
        boxId.row = (++flag_index) % 10;
        SDL_Rect sdstf = { dst.x + viewport.x - 12, viewport.y + dst.y - 48, 50, 50};
        rm.RenderCharacter(&sdstf, boxId);
    }


}
