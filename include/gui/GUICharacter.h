#ifndef GUI__GUICHARACTER_H_INCLUDED
#define GUI__GUICHARACTER_H_INCLUDED

#include "model/Character.h"

using namespace game::model;

class GUICharacter : public Character
{
    public:
        GUICharacter();
        void Render(SDL_Rect& viewport, ResourceManager& rm);
};

#endif // GUI__GUICHARACTER_H_INCLUDED
