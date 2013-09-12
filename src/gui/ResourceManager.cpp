
#include "gui/ResourceManager.h"

using namespace game::gui;

ResourceManager::ResourceManager() {
}

ResourceManager::ResourceManager(SDL_Renderer * renderer) {
    this -> renderer = renderer;
}

ResourceManager& ResourceManager::Load(SDL_Renderer * renderer, const string& mapCatalogPath, const string& characterCatalogPath) {
    this -> renderer = renderer;
    LoadCatalog(mapCatalogPath, WHE_MAP_CATALOG_CODE);
    LoadCatalog(characterCatalogPath, WHE_CHARACTER_CATALOG_CODE);
    return *this;
}

ResourceManager& ResourceManager::LoadCatalog(const string& path, const string& code) {
    string name;
    Uint16 cols; Uint16 rows;
    Uint16 sw; Uint16 sh;

    Log::Write({"Loading catalog from ", path}, {"catalog", code});
    ifstream file(path, ifstream::in);
    while (file >> name >> cols >> rows >> sw >> sh) {
        resources[code].push_back(Sprite());
        resources[code].back().LoadCtteSprite(name, renderer, cols, rows, sw, sh);
    }
    file.close();
    Log::Write({"Completed loading from", path}, {"catalog", code});
    return *this;
}

bool ResourceManager::Render(const string& catalogName, SDL_Rect * dst, SpriteID id) {
    bool rendered = false;
    if (resources.find(catalogName) != resources.end())
        return Render(resources[catalogName], dst, id);
    return rendered;
}

bool ResourceManager::Render(vector<Sprite>& catalog, SDL_Rect * dst, SpriteID id) {
    return catalog[id.ID].Render(renderer, dst, (Uint16) id.col, (Uint16) id.row);
}

bool ResourceManager::RenderMap(SDL_Rect * dst, SpriteID id) {
    return Render(WHE_MAP_CATALOG_CODE, dst, id);
}

bool ResourceManager::RenderCharacter(SDL_Rect * dst, SpriteID id) {
    return Render(WHE_CHARACTER_CATALOG_CODE, dst, id);
}
