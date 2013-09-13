
#include "gui/GUIMap.h"

GUIMap::GUIMap()
{

}

// TODO Manage the vector as array to improve performance call methods
void GUIMap::Render(Sint16 sx, Sint16 sy, ResourceManager& rm) {
    SDL_Rect dst = { sx, sy, 64, 64 };
    int dx = 0;
    for (int i=0;i<rows;i++) {
        dst.y = sy + (i * 16) - 64;
        dx = (i % 2) * - 32;
        for (int j=0;j<cols;j++) {
            dst.x = sx + dx + (j * 64);
            rm.RenderMap(&dst, elements[j][i]);
        }
    }
}
