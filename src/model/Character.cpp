
#include "model/Character.h"

Character::Character()
{
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

Uint16 Character::Status(Uint16 flags, bool erase) {
    if (erase) return (status &= ~flags);
    else return (status |= flags);
}

Uint16 Character::Is(Uint16 flags) {
    return status & flags;
}
