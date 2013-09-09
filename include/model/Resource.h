
#ifndef MODEL__RESOURCE_H_INCLUDED
#define MODEL__RESOURCE_H_INCLUDED

#include <SDL2\SDL.h>
#include <SDL2\SDL_stdinc.h>

using namespace std;

#define RT_SPRITE       1
#define RT_SPRITE       2
#define RT_SPRITE       4
#define RT_SPRITE       8

namespace game { namespace model {

    typedef struct _ResourceID
    {
        Uint8 type;
        Uint16 ID;
        Uint8 row;
        Uint8 col;
    } ResourceID, *LPResourceID;

}}

#endif // MODEL__RESOURCE_H_INCLUDED
