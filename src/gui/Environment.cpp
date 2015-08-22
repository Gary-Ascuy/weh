
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

struct ClientPull {
    xGame * game;
    game::net::Socket * client;
    Uint32 * lastUpdate;
};

int server_task_pull(void * data) {

    ClientPull * pull = (ClientPull *) data;
    xGame * game = pull -> game;
    game::net::Socket * client = pull -> client;
    Uint32 * lastUpdate = pull -> lastUpdate;
    Personage package;

    while (true) {
        if (client -> Recv((void*) &package, sizeof(Personage)) > 0) {
            game -> Lock();
            game -> p.id = package.id;
            game -> p.x = package.x;
            game -> p.y = package.y;
            game -> lastUpdate++;
            *lastUpdate = game -> lastUpdate;
            iLogger(iINFO << iTAGS({"server", "recv"}) << "Update");
            game -> Unlock();
        }
    }
    return 0;
}

int server_attend_task(void * data) {
    iLogger(iINFO << iTAGS({"server_client_attend"}) << "int server_attend_task(void * data)");
    Uint32 lastUpdate = 0;

    xData * xdata = (xData*) data;
    xGame * game = xdata -> game;
    Settings * settings = xdata -> settings;
    SDL_mutex * sync = xdata -> sync;

    game::net::Socket client(xdata -> socket);

    ClientPull pull;
    pull.game = game;
    pull.client = &client;
    pull.lastUpdate = &lastUpdate;
    SDL_CreateThread(server_task_pull, "client_pull", (void*)&pull);

    Personage package;
    bool running = true;
    while (running) {

        game -> Lock();
        // server don't send updates
        if (lastUpdate < game -> lastUpdate) {
            package.id = game -> p.id;
            package.x = game -> p.x;
            package.y = game -> p.y;
            client.Send((void*) &package, sizeof(Personage));
            iLogger(iINFO << iTAGS({"server", "send"}) << "Update");
            lastUpdate = game -> lastUpdate;
        }
        game -> Unlock();
    }
}

int server_task(void * data) {
    iLogger(iINFO << iTAGS({"server"}) << "1 server_task(void * data)");
    try {
        xData * xdata = (xData*) data;
        xGame * game = xdata -> game;
        Settings * settings = xdata -> settings;
        SDL_mutex * sync = xdata -> sync;

        game::net::TCPServer tcp_server(settings -> port);
        //SDL_UnlockMutex(sync);

        TCPsocket connection;
        while ((connection = tcp_server.Accept())) {
            xData * idata = new xData();
            idata -> game = game;
            idata -> settings = settings;
            idata -> socket = connection;
            idata -> sync = sync;
            SDL_CreateThread(server_attend_task, "server_attend", (void*)idata);
        }
    } catch (...) {
        iLogger(iINFO << iTAGS({"ERROR", "server"}) << "fatal error has been occurs starting");
    }
    return EXIT_SUCCESS;
}

int client_task_pull(void * data) {
    ClientPull * pull = (ClientPull *) data;
    xGame * game = pull -> game;
    game::net::Socket * client = pull -> client;

    bool running = true;
    Personage package;

    while (running) {
        if (client -> Recv((void*) &package, sizeof(Personage)) > 0) {
            game -> Lock();
            game -> p.id = package.id;
            game -> p.x = package.x;
            game -> p.y = package.y;
            game -> Unlock();
            iLogger(iINFO << iTAGS({"client", "resv"}) << "Update client");
        }
    }
}

int client_task(void * data) {
    iLogger(iINFO << iTAGS({"client"}) << "1 client_task(void * data)");

    try {
        xData * xdata = (xData *) data;
        xGame * game = xdata -> game;
        Settings * settings = xdata -> settings;
        SDL_mutex * sync = xdata -> sync;

        //SDL_LockMutex(sync);
        iLogger(iINFO << iTAGS({"client"}) << "2 Waiting ....");
        SDL_Delay(3000);
        iLogger(iINFO << iTAGS({"client"}) << "3 game::net::Socket client(settings -> host, settings -> port)");
        game::net::Socket client(settings -> host, settings -> port);
        //SDL_UnlockMutex(sync);

        ClientPull pull;
        pull.game = game;
        pull.client = &client;
        SDL_CreateThread(client_task_pull, "client_pull", (void*)&pull);

        Personage package;
        bool running = true;

        Uint32 lastUpdateSend = 0;
        while (running) {

            game -> Lock();
            if (lastUpdateSend < game -> lastUpdate) {
                package.id = game -> p.id;
                package.x = game -> p.x;
                package.y = game -> p.y;

                client.Send((void*) &package, sizeof(Personage));
                lastUpdateSend = game -> lastUpdate;
                iLogger(iINFO << iTAGS({"client", "send"}) << "Update client");
            }
            game -> Unlock();
            SDL_Delay(30);
        }
    } catch (const NetException& ne) {
        iLogger(iINFO << iTAGS({"ERROR", "client"}) << ne.what());
    } catch (...) {
        iLogger(iINFO << iTAGS({"ERROR", "client"}) << "fatal error has been occurs starting");
    }
    return EXIT_SUCCESS;
}

Environment& Environment::Run(Settings& settings) {
    iLogger(iINFO << "Running ...");
    xGame sGame; xGame cGame;
    SDL_mutex * sync = SDL_CreateMutex();

    xData sdata = { &sGame, &settings, sync };
    xData cdata = { &cGame, &settings, sync };

    if (settings.server) {
        //SDL_LockMutex(sync);
        SDL_CreateThread(server_task, "server", (void*)&sdata);
    }

    if (settings.client) {
        SDL_CreateThread(client_task, "client", (void*)&cdata);
    }

    Uint32 window_mode = SDL_WINDOW_SHOWN;
    if (settings.fullscreen) window_mode |= SDL_WINDOW_FULLSCREEN;
    game::gui::GUIGame game(&cGame, WEH_NAME, settings.width, settings.height, window_mode);
    game.Load().Loop();
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
