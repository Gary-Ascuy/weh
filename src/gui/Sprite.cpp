
#include "gui/Sprite.h"

using namespace game::gui;

Sprite::Sprite() {
    texture = NULL;
    cols = rows = 0;
    w = h = 0;
}

Sprite::Sprite(const string& path, SDL_Renderer * renderer, Uint16 cols, Uint16 rows, Uint16 w, Uint16 h) {
    LoadCtteSprite(path, renderer, cols, rows, w, h);
}

Sprite& Sprite::LoadCtteSprite(const string& path, SDL_Renderer * renderer, Uint16 cols, Uint16 rows, Uint16 sw, Uint16 sh) {
    this -> cols = cols; this -> rows = rows;
    this -> w = sw; this -> h = sh;
    this -> path = path;

    iLogger(iINFO << iTAGS({"sprite"}) << "Sprite loaded from " << path);
    texture = IMG_LoadTexture(renderer, path.c_str());

    rects.resize(cols);
    for (int c = 0;c < cols;++c) {
        rects[c].resize(rows);
        for (int r = 0;r < rows;++r) {
            SDL_Rect & rect = rects[c][r];
            rect.x = c * w; rect.y = r * h;
            rect.h = h; rect.w = w;
            LogRect(rect);
        }
    }
    return *this;
}

SDL_Rect * Sprite::Get(Uint16 col, Uint16 row) {
    SDL_Rect * src = NULL;
    if (col >= 0 && col < cols && row >= 0 && row < rows) {
        src = &rects[col][row];
    }
    return src;
}

bool Sprite::Render(SDL_Renderer * renderer, SDL_Rect * dst, Uint16 col, Uint16 row) {
    bool rendered = false;
    if (renderer != NULL && texture != NULL) {
        SDL_Rect * src = Get(col, row);
        if (src != NULL) {
            SDL_RenderCopy(renderer, texture, src, dst);
            rendered = true;
        }
    }
    return rendered;
}

string Sprite::Path() {
    return path;
}

SDL_Texture * Sprite::Texture() {
    return texture;
}

Uint16 Sprite::Cols() {
    return cols;
}

Uint16 Sprite::Rows() {
    return rows;
}

Uint16 Sprite::W() {
    return w;
}

Uint16 Sprite::H() {
    return h;
}

void Sprite::LogRect(SDL_Rect& rect) {
    iLogger(iFINEST << setw(10) << rect.x << setw(10) << rect.y << setw(10) << rect.h << setw(10) << rect.w);
}
