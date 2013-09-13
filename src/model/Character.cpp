
#include "model/Character.h"

Character::Character()
{
    //ctor
}

Character& Character::Src(Uint16 x, Uint16 y) {
    src.x = x;
    src.y = y;
    return *this;
}

Character& Character::Dst(Uint16 x, Uint16 y) {
    dst.x = x;
    dst.y = y;
    return *this;
}
