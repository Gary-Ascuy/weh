
#ifndef GUI__SPRITE_H_INCLUDED
#define GUI__SPRITE_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>

#include "ilog/Logger.h"

using namespace std;

namespace game { namespace gui {
    class Sprite {
    public:
        Sprite();
        Sprite(const string& path, SDL_Renderer * renderer, Uint16 cols, Uint16 rows, Uint16 w, Uint16 h);
        Sprite& LoadCtteSprite(const string& path, SDL_Renderer * renderer, Uint16 cols, Uint16 rows, Uint16 sw, Uint16 sh);

        SDL_Rect * Get(Uint16 col, Uint16 row);
        bool Render(SDL_Renderer * renderer, SDL_Rect * dst, Uint16 col, Uint16 row);

        string Path();
        SDL_Texture * Texture();
        Uint16 Cols();
        Uint16 Rows();
        Uint16 W();
        Uint16 H();

    private:
        void LogRect(SDL_Rect& rect);

    private:
        string path;
        SDL_Texture * texture;
        vector< vector<SDL_Rect> > rects;

        Uint16 cols;
        Uint16 rows;

        Uint16 w;
        Uint16 h;
    };
}}

#endif // GUI__SPRITE_H_INCLUDED
