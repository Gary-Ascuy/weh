
#include "gui/GUIGame.h"

using namespace game::gui;

GUIGame::GUIGame(xGame * game, const string& title, Sint16 width, Sint16 height, Uint32 window_mode, Uint32 render_mode) {
    this -> game = game;
    iLogger(iINFO << title << " -Size=" << width << "x" << height << " -WindowMode=" << window_mode << " -RenderMode=" << render_mode);
    Initialize(title, width, height, window_mode, render_mode);
}

GUIGame::~GUIGame() {
    iLogger(iINFO << "Destroying renderer and window");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void GUIGame::Initialize(const string& title, Sint16 width, Sint16 height, Uint32 window_mode, Uint32 render_mode) {
    iLogger(iINFO << "Inicializing SDL, IMG, TTF, renderer and window");
    this -> width = width;
    this -> height = height;

    // creating windows and render
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height, window_mode);
    renderer = SDL_CreateRenderer(window, -1, render_mode);

    if (!window || !renderer) {
        iLogger(iERROR << "Error initializing Windows and Render" << SDL_GetError());
        exit(WEH_ERR_WIN);
    }
}

GUIGame& GUIGame::Load() {
    iLogger(iINFO << "Loading resources (IMG, FONT)");
    iLogger(iINFO << iTAGS({"resources"}) << "Loading resources (IMG, FONT)");
    rm.Load(renderer, "resources\\map.sprite", "resources\\character.sprite");
    iLogger(iINFO << iTAGS({"resources"}) << "End loading resources");

    map.LoadFromFile("resources\\wild-world.map");
    return *this;
}

GUIGame& GUIGame::Loop() {
    auto running = true;

    //Select fields
    SDL_Rect selection;
    bool selecting = false;
    SpriteID select = { 8, 0, 0 };

    SpriteID menu = { 13, 0, 0 };
    SpriteID menu2 = { 14, 0, 0 };
    SDL_Rect menuRect = { width - 190, height - 184, 190, 184 };
    SDL_Rect menuRect2 = { 0, height - 184, width - 190, 184 };

    SpriteID button = { 16, 0, 0 };
    SDL_Rect buttonRect = { 10, height - 35, 30, 30 };

    // viewport
    viewport.x = 0;
    viewport.y = 0;

    // player
    GUICharacter player(9);
    GUICharacter player2(10);
    GUICharacter player3(11);
    GUICharacter player4(12);

    player.Start(240, 240);
    player2.Start(340, 240);
    player3.Start(440, 240);
    player4.Start(540, 240);

    SDL_Point mouse;
    //SDL_Point selectionStart;
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
                            player.Select(selection);
                            player2.Select(selection);
                            player3.Select(selection);
                            player4.Select(selection);
                            break;
                        case SDL_BUTTON_RIGHT:
                            int sc = 0;
                            int df = 16;
                            if (player.Is(WEH_CHARACTER_STATUS_SELECTED)) {
                                //player.Dst(, );
                                //sc++;
                                game -> Lock();
                                game -> p.x = event.button.x - viewport.x;
                                game -> p.y = event.button.y - viewport.y;
                                game -> lastUpdate++;
                                iLogger(iINFO << iTAGS({"client", "gui"}) << "Needs update from SDL_BUTTON_RIGHT");
                                game -> Unlock();
                            }
                            if (player2.Is(WEH_CHARACTER_STATUS_SELECTED)) {
                                player2.Dst(event.button.x - viewport.x + sc * df, event.button.y - viewport.y + sc * df);
                                sc++;
                            }
                            if (player3.Is(WEH_CHARACTER_STATUS_SELECTED)) {
                                player3.Dst(event.button.x - viewport.x + sc * df, event.button.y - viewport.y + sc * df);
                                sc++;
                            }
                            if (player4.Is(WEH_CHARACTER_STATUS_SELECTED)) {
                                player4.Dst(event.button.x - viewport.x + sc * df, event.button.y - viewport.y + sc * df);
                                sc++;
                            }
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button) {
                        case SDL_BUTTON_LEFT:
                            selecting = true;
                            player.Status(WEH_CHARACTER_STATUS_SELECTED, true);
                            player2.Status(WEH_CHARACTER_STATUS_SELECTED, true);
                            player3.Status(WEH_CHARACTER_STATUS_SELECTED, true);
                            player4.Status(WEH_CHARACTER_STATUS_SELECTED, true);
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
                    //if (WEH_IS_DINR( buttonRect, mouse.x, mouse.y )) button.row = 0; else button.row = 1;
                    break;
            }
        }

        /* MOUSE */
        int viewInc = 4;
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
        //player2.Render(viewport, rm);
        //player3.Render(viewport, rm);
        //player4.Render(viewport, rm);

        if (selecting) rm.RenderCharacter(&selection, select);

        rm.RenderCharacter(&menuRect, menu);
        rm.RenderCharacter(&menuRect2, menu2);
        rm.RenderCharacter(&buttonRect, button);

        // UPDATE
        game -> Lock();
        player.Dst(game -> p.x, game -> p.y);
        game -> Unlock();

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
