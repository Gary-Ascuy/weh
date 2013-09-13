#ifndef MODEL__CHARACTER_H_INCLUDED
#define MODEL__CHARACTER_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "model/Log.h"
#include "gui/TimeController.h"
#include "model/Resource.h"
#include "gui/ResourceManager.h"
#include "gui/GUIMap.h"

#define WEH_CHARACTER_STATUS_SELECTED   1
#define WEH_CHARACTER_STATUS_WALKING    2
#define WEH_CHARACTER_STATUS_FIRE       4

class Character
{
    public:
        Character();

        Character& Src(Uint16 x, Uint16 y);
        Character& Dst(Uint16 x, Uint16 y);

        Uint16 Status(Uint16 flags, bool erase = false);
        Uint16 Is(Uint16 flags);

    protected:
        SDL_Point src;
        SDL_Point dst;
        Uint16 status;
};

#endif // MODEL__CHARACTER_H_INCLUDED
