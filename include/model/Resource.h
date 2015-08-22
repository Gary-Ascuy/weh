
#ifndef MODEL__RESOURCE_H_INCLUDED
#define MODEL__RESOURCE_H_INCLUDED


using namespace std;

namespace game { namespace model {

    typedef struct _SpriteID {
        uint16_t ID;
        uint8_t row;
        uint8_t col;
    } SpriteID, *LPSpriteID;

    typedef union _SpriteIDLoader {
        SpriteID sprite;
        uint32_t value;
    } SpriteIDLoader, *LPSpriteIDLoader;

}}

#endif // MODEL__RESOURCE_H_INCLUDED
