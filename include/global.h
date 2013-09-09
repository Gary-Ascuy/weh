
#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

/**
 * Error codes
 **/
#define WEH_SUCCESS    0

#define WEH_ERR_SDL   -1
#define WEH_ERR_IMG   -2
#define WEH_ERR_TTF   -3
#define WEH_ERR_WIN   -4

#define WEH_ERR_MISSING_RESOURCE   1

/**
 * Library modes
 **/
#define WEH_INIT_SDL SDL_INIT_EVERYTHING
#define WEH_INIT_IMG IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP

/**
 * System modes
 **/
#define WEH_WINDOW_MODE /*SDL_WINDOW_FULLSCREEN |*/ SDL_WINDOW_SHOWN
#define WEH_RENDER_MODE SDL_RENDERER_ACCELERATED

/**
 * Application settings
 **/
#define WEH_WIDTH 1024
#define WEH_HEIGHT 768
#define WEH_NAME "World of Elemental Heroes"

#endif // GLOBAL_H_INCLUDED
