#ifndef GUI__GUIMAP_H_INCLUDED
#define GUI__GUIMAP_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "gui/TimeController.h"
#include "model/Resource.h"
#include "model/Map.h"
#include "gui/ResourceManager.h"

#include "ilog/Logger.h"

using namespace game::model;

class GUIMap : public Map
{
    public:
        GUIMap();
        void Render(Sint16 sx, Sint16 sy, ResourceManager& rm);
    private:
};

#endif // GUI__GUIMAP_H_INCLUDED
