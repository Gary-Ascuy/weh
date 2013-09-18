
#ifndef GUI__ENVIRONMENT_H__INCLUDED
#define GUI__ENVIRONMENT_H__INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_net.h>

#include <cstdlib>

#include "ilog/Logger.h"
#include "excp/GuiException.h"

/**
 * Library modes
 **/
#define WEH_INIT_SDL SDL_INIT_EVERYTHING
#define WEH_INIT_IMG IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP

/**
 * Systems availables
 */
#define WEH_SDL2                1
#define WEH_SDL2_IMG            2
#define WEH_SDL2_TTF            4
#define WEH_SDL2_NET            8

#define WEH_FULL_ENV            (~0)

using namespace game::excp;

namespace game { namespace gui {

    class Environment {
    public:
        Environment(uint16_t systems, Uint32 sdl_flags = WEH_INIT_SDL, int img_flags = WEH_INIT_IMG);
        ~Environment();
        Environment& Run();
        int Success();

    private:
        void LogSystems();

    private:
        uint16_t systems;
    };

}}

#endif // GUI__ENVIRONMENT_H__INCLUDED
