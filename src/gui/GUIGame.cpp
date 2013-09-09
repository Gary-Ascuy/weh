
#include "gui/GUIGame.h"

using namespace game::gui;

GUIGame::GUIGame(const string& title, Sint16 width, Sint16 height, Uint32 window_mode, Uint32 render_mode) {
    stringstream message;
    message << title << " -Size=" << width << "x" << height;
    message << " -WindowMode=" << window_mode << " -RenderMode=" << render_mode;
    Log::Write(message.str());

    Initialize(title, width, height, window_mode, render_mode);
}

GUIGame::~GUIGame() {
    Log::Write("Destroying renderer and window");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void GUIGame::Initialize(const string& title, Sint16 width, Sint16 height, Uint32 window_mode, Uint32 render_mode) {
    Log::Write("Inicializing SDL, IMG, TTF, renderer and window");

    // Init all SDL systems
    if (SDL_Init(WEH_INIT_SDL) < 0) {
        Log::WriteErr("Error initializing SDL", SDL_GetError());
        SDL_Quit();
        exit(WEH_ERR_SDL);
    } else atexit(SDL_Quit);

    // Init img system
    if (IMG_Init(WEH_INIT_IMG) < 0) {
        Log::WriteErr("Error initializing IMG", IMG_GetError());
        exit(WEH_ERR_IMG);
    } else atexit(IMG_Quit);

    // Init ttf system
    if (TTF_Init() < 0) {
        Log::WriteErr("Error initializing TTF", TTF_GetError());
        exit(WEH_ERR_TTF);
    } else atexit(TTF_Quit);

    // creating windows and render
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height, window_mode);
    renderer = SDL_CreateRenderer(window, -1, render_mode);

    if (!window || !renderer) {
        Log::WriteErr("Error initializing Windows and Render", SDL_GetError());
        exit(WEH_ERR_WIN);
    }
}

GUIGame& GUIGame::Load() {
    Log::Write("Loading resources (IMG, FONT)");
    return *this;
}

GUIGame& GUIGame::Loop() {
    auto running = true;

    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE: running = false; break;
                    }
                    break;
                case SDL_QUIT: running = false; break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    return *this;
}

int GUIGame::Success() {
    return WEH_SUCCESS;
}
