#ifndef GUI__GUICHARACTER_H_INCLUDED
#define GUI__GUICHARACTER_H_INCLUDED

#include "model/Character.h"

#define WEH_IS_DINR(r, px, py) (px >= r.x && px < (r.x + r.w) && py >= r.y && py < (r.y + r.h))
#define WEH_IS_RINR(a, b) WEH_IS_DINR(a, b.x, b.y) || WEH_IS_DINR(a, b.x + b.w, b.y) || WEH_IS_DINR(a, b.x, b.y + b.h) || WEH_IS_DINR(a, b.x + b.w, b.y + b.h)

using namespace game::model;

namespace game { namespace gui {

    class GUICharacter : public Character
    {
    public:
        GUICharacter(Uint16 selectID);
        void Render(SDL_Rect& viewport, ResourceManager& rm);
        void Select(SDL_Rect& selection);

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

}}

#endif // GUI__GUICHARACTER_H_INCLUDED
