
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
    this -> width = width;
    this -> height = height;

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

    Log::Write({"Start loading resources"}, {"resources"});
    rm.Load(renderer, "resources\\map.sprite", "resources\\character.sprite");
    Log::Write({"End loading resources"}, {"resources"});

    map.LoadFromFile("resources\\wild-world.map");
    return *this;
}

bool isIN(int x, int xx, int ww) {
    return x >= xx && x <= (xx + ww);
}

GUIGame& GUIGame::Loop() {
    auto running = true;

    //Select fields
    SDL_Rect selection;
    bool selecting = false;
    SpriteID select = { 8, 0, 0 };

    // viewport
    viewport.x = 0;
    viewport.y = 0;

    // player
    GUICharacter player(9);
    player.Src(240, 240).Dst(240, 240);

    SDL_Point mouse;
    SDL_Event event;
    TimeController time(25.0);
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
                case SDL_MOUSEBUTTONUP:
                    switch (event.button.button) {
                        case SDL_BUTTON_LEFT:
                            selecting = false;
                            player.Status(WEH_CHARACTER_STATUS_SELECTED);
                            break;
                        case SDL_BUTTON_RIGHT:
                            if (player.Is(WEH_CHARACTER_STATUS_SELECTED)) {
                                player.Dst(event.button.x - viewport.x, event.button.y - viewport.y);
                            }
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button) {
                        case SDL_BUTTON_LEFT:
                            selecting = true;
                            selection = { event.button.x, event.button.y, 0, 0 };
                            break;
                        case SDL_BUTTON_RIGHT:
                            break;
                        case SDL_BUTTON_MIDDLE:
                            break;

                    }
                    break;
                case SDL_MOUSEMOTION:
                    mouse.x = event.motion.x;
                    mouse.y = event.motion.y;

                    selection.w = abs(event.motion.x - selection.x);
                    selection.h = abs(event.motion.y - selection.y);
                    break;
            }
        }

        /* MOUSE */
        int viewInc = 3;
        if (mouse.x < 50) {
            int ddx = (50 - mouse.x)/5 + viewInc;
            viewport.x += ddx;
            if (viewport.x > 0) viewport.x = 0;
        }
        if (mouse.x > width - 50) {
            int ddx = (50 - (width - mouse.x))/5 + viewInc;
            viewport.x -= ddx;
            int max = (25 * 16 + 64 + 16) - 1024;
            if (viewport.x < max) viewport.x = max;
        }
        if (mouse.y < 50) {
            int ddx = (50 - mouse.y)/5 + viewInc;
            viewport.y += ddx;
            if (viewport.y > 0) viewport.y = 0;
        }
        if (mouse.y > height - 50) {
            int ddx = (50 - (height - mouse.y))/5 + viewInc;
            viewport.y -= ddx;
            int max = (72 * 16 + 16 - 64) - 768;
            if (viewport.y < -max) viewport.y = -max;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        map.Render(viewport.x, viewport.y, rm);
        player.Render(viewport, rm);
        if (selecting) rm.RenderCharacter(&selection, select);

        SDL_RenderPresent(renderer);
        time.Wait();
    }
    return *this;
}

int GUIGame::Success() {
    return WEH_SUCCESS;
}

SDL_Renderer * GUIGame::Renderer() {
    return renderer;
}
