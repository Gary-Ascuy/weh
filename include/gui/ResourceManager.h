
#ifndef GUI__RESOURCEMANAGER_H__INCLUDED
#define GUI__RESOURCEMANAGER_H__INCLUDED

#include <map>
#include <vector>
#include <iostream>
#include <fstream>

#include "model/Resource.h"
#include "gui/Sprite.h"

#include "ilog/Logger.h"

#define WHE_MAP_CATALOG_CODE "character.sprite"
#define WHE_CHARACTER_CATALOG_CODE "map.sprite"

using namespace std;
using namespace game::model;
using namespace game::gui;

namespace game { namespace gui {

    class ResourceManager
    {
    public:
        ResourceManager();
        ResourceManager(SDL_Renderer * renderer);

        ResourceManager& Load(SDL_Renderer * renderer, const string& mapCatalogPath, const string& characterCatalogPath);
        ResourceManager& LoadCatalog(const string& mapCatalogPath, const string& code);

        bool Render(const string& catalogName, SDL_Rect * dst, SpriteID id);
        bool Render(vector<Sprite>& catalog, SDL_Rect * dst, SpriteID id);

        bool RenderMap(SDL_Rect * dst, SpriteID id);
        bool RenderCharacter(SDL_Rect * dst, SpriteID id);

    private:
        SDL_Renderer * renderer;
        map< string, vector<Sprite> > resources;

    };

}}

#endif // GUI__RESOURCEMANAGER_H__INCLUDED
