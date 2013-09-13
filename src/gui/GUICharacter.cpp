
#include "gui/GUICharacter.h"

GUICharacter::GUICharacter(Uint16 selectID)
{
    status = 0;
    player = { 0, 0, 0 };
    flag = { 7, 0, 0 };
    selected = {selectID, 0, 0};

    playerRect.w = playerRect.h = 32;
    flagRect.w = flagRect.h = 50;
    selectedRect.w = selectedRect.h = 50;

    tick_player = 0;
    tick_flag = 0;
    tick_select = 0;

    last_tick = 0;
}

void GUICharacter::Render(SDL_Rect& viewport, ResourceManager& rm) {
    int dx = src.x - dst.x;
    int dy = src.y - dst.y;
    status &= ~WEH_CHARACTER_STATUS_WALKING;

    Uint32 now = SDL_GetTicks();
    playerRect.x = src.x + viewport.x - playerRect.w/2;
    playerRect.y = src.y + viewport.y - playerRect.h;

    if (now - last_tick > 35) {
        last_tick = now;

        if (abs(dx) > 10) {
            Status(WEH_CHARACTER_STATUS_WALKING);
            if (dx > 0) src.x -= 5;
            else src.x += 5;
        }

        if (abs(dy) > 10) {
            Status(WEH_CHARACTER_STATUS_WALKING);
            if (dy > 0) src.y -= 5;
            else src.y += 5;
        }

        if (Is(WEH_CHARACTER_STATUS_WALKING)) {
            player.col = ((int)(tick_player += 1)) % 4;
        }
    }

    if (abs(dx) > abs(dy)) {
        if (dx > 0) player.row = 1;
        else player.row = 2;
    } else {
        if (dy > 0) player.row = 3;
        else player.row = 0;
    }

    // selected render
    if (Is(WEH_CHARACTER_STATUS_SELECTED)) {
        selectedRect.x = src.x + viewport.x - 25;
        selectedRect.y = src.y + viewport.y - 30;
        selected.row = ((int) (tick_select += 0.2)) % 10;
        rm.RenderCharacter(&selectedRect, selected);
    }

    // render character
    playerRect.x = src.x + viewport.x - playerRect.w/2;
    playerRect.y = src.y + viewport.y - playerRect.h;
    rm.RenderCharacter(&playerRect, player);

    // flag render
    if (Is(WEH_CHARACTER_STATUS_WALKING)) {
        flag.row = ((int)(tick_flag += 1)) % 10;
        flagRect.x = dst.x + viewport.x - 12;
        flagRect.y = dst.y + viewport.y - 48;
        rm.RenderCharacter(&flagRect, flag);
    }
}

SDL_Rect * GUICharacter::Block() {
    return &playerRect;
}
