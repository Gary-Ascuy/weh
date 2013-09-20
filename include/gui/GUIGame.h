
#ifndef GUI__GUIGAME_H_INCLUDED
#define GUI__GUIGAME_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_ttf.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>

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

    struct Settings {
        bool client, server;
        char * host;
        uint16_t port;

        bool fullscreen;
        uint16_t width, height;
    };

    struct Personage {
        uint16_t id;
        uint16_t x, y;

    public:
        Personage() { id = x = y = 0; }
    };

    struct xGame {
        Uint32 lastUpdate;
        SDL_mutex * mutex;
        Personage p;


    public:
        xGame() {
            lastUpdate = 0;
            mutex = SDL_CreateMutex();
        }

        int Lock() { return SDL_LockMutex(mutex); }
        int Unlock() { return SDL_UnlockMutex(mutex); }

    };

    struct xData {
        xGame * game;
        Settings * settings;
        SDL_mutex * sync;
        TCPsocket socket;
    };


    class GUIGame {
    public:
        GUIGame(xGame * game, const string& title, Sint16 width, Sint16 height, Uint32 window_mode = WEH_WINDOW_MODE, Uint32 render_mode = WEH_RENDER_MODE);
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
        xGame * game;
    };

}}

#endif // GUI__GUIGAME_H_INCLUDED
