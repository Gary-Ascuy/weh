
#include "gui/Environment.h"

using namespace game::gui;

Environment::Environment(uint16_t systems, Uint32 sdl_flags, int img_flags) : systems(0) {
    iLogger(iFINE << "Environment::Environment()");
    if (systems & WEH_SDL2) {
        int err = SDL_Init(sdl_flags);
        if (err < 0) throw GuiException(SDL_GetError());
        else this -> systems |= WEH_SDL2;
    }

    if (systems & WEH_SDL2_IMG) {
        int err = IMG_Init(img_flags);
        if (err < 0) throw GuiException(IMG_GetError());
        else this -> systems |= WEH_SDL2_IMG;
    }

    if (systems & WEH_SDL2_TTF) {
        int err = TTF_Init();
        if (err < 0) throw GuiException(TTF_GetError());
        else this -> systems |= WEH_SDL2_TTF;
    }

    if (systems & WEH_SDL2_NET) {
        int err = SDLNet_Init();
        if (err < 0) throw GuiException(SDLNet_GetError());
        else this -> systems |= WEH_SDL2_NET;
    }
    LogSystems();
}

Environment::~Environment() {
    iLogger(iFINE << "Environment::~Environment()");
    if (systems & WEH_SDL2_NET) SDLNet_Quit();
    if (systems & WEH_SDL2_TTF) TTF_Quit();
    if (systems & WEH_SDL2_IMG) IMG_Quit();
    if (systems & WEH_SDL2) SDL_Quit();
}

Environment& Environment::Run() {
    iLogger(iINFO << "Running ...");
    return *this;
}

int Environment::Success() {
    return EXIT_SUCCESS;
}

void Environment::LogSystems() {
    if (systems & WEH_SDL2) iLogger(iFINE << "WEH_SDL2");
    if (systems & WEH_SDL2_IMG) iLogger(iFINE << "WEH_SDL2_IMG");
    if (systems & WEH_SDL2_TTF) iLogger(iFINE << "WEH_SDL2_TTF");
    if (systems & WEH_SDL2_NET) iLogger(iFINE << "WEH_SDL2_NET");
}
