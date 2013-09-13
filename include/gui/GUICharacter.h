#ifndef GUI__GUICHARACTER_H_INCLUDED
#define GUI__GUICHARACTER_H_INCLUDED

#include "model/Character.h"


#define WEH_IS_DINR(r, x, y) (x >= r.x && x < (r.x + r.w) && y >= r.y && y < (r.y + r.h))
#define WEH_IS_RINR(a, b) WEH_IS_DINR(a, b.x, b.y)
// || WEH_IS_DINR(a, b.x + b.w, b.y) || WEH_IS_DINR(a, b.x, b.y + b.h) || WEH_IS_DINR(a, b.x + b.w, b.y + b.h)

using namespace game::model;

class GUICharacter : public Character
{
    public:
        GUICharacter(Uint16 selectID);
        void Render(SDL_Rect& viewport, ResourceManager& rm);
        SDL_Rect * Block();

    private:
        SpriteID player;
        SpriteID flag;
        SpriteID selected;

        SDL_Rect playerRect;
        SDL_Rect flagRect;
        SDL_Rect selectedRect;

        double tick_player;
        double tick_flag;
        double tick_select;

        Uint32 last_tick;
};

#endif // GUI__GUICHARACTER_H_INCLUDED
