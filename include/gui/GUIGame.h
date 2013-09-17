
#ifndef GUI__GUIGAME_H_INCLUDED
#define GUI__GUIGAME_H_INCLUDED

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
#include "gui/ResourceManager.h"
#include "gui/GUIMap.h"
#include "gui/GUICharacter.h"

#include "ilog/Logger.h"

using namespace std;
using namespace game::model;

namespace game { namespace gui {

    class GUIGame {
    public:
        GUIGame(const string& title, Sint16 width, Sint16 height, Uint32 window_mode = WEH_WINDOW_MODE, Uint32 render_mode = WEH_RENDER_MODE);
        ~GUIGame();

        GUIGame& Load();
        GUIGame& Loop();
        int Success();

        SDL_Renderer * Renderer();

    private:
        void Initialize(const string& title, Sint16 width, Sint16 height, Uint32 window_mode, Uint32 render_mode);

    private:
        Sint16 width;
        Sint16 height;

        SDL_Window * window = NULL;
        SDL_Renderer * renderer = NULL;

        ResourceManager rm;
        GUIMap map;
        SDL_Rect viewport;
    };

}}

#endif // GUI__GUIGAME_H_INCLUDED
