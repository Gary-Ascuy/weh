
#ifndef MODEL__RESOURCE_H_INCLUDED
#define MODEL__RESOURCE_H_INCLUDED

#include <SDL2\SDL.h>
#include <SDL2\SDL_stdinc.h>

using namespace std;

namespace game { namespace model {

    typedef struct _SpriteID {
        Uint16 ID;
        Uint8 row;
        Uint8 col;
    } SpriteID, *LPSpriteID;

    typedef union _SpriteIDLoader {
        SpriteID sprite;
        Uint32 value;
    } SpriteIDLoader, *LPSpriteIDLoader;

}}

#endif // MODEL__RESOURCE_H_INCLUDED
