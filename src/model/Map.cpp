
#include "model/Map.h"

using namespace game::model;

Map::Map() {
}

Map::Map(Uint16 cols, Uint16 rows, Uint8 w, Uint8 h)
{
    Start(cols, rows);
}

Map& Map::Start(Uint16 cols, Uint16 rows) {
    this -> cols = cols;
    this -> rows = rows;

    elements.resize(cols);
    for (auto i = 0;i < cols;++i)
    {
        elements[i].resize(rows);
    }
    return *this;
}

Map& Map::Set(Uint16 col, Uint16 row, SpriteID resorce) {
    if (col >= 0 && col < cols && row >= 0 && row < rows) {
        elements[col][row] = resorce;
    }
    return *this;
}

SpriteID Map::Get(Uint16 col, Uint16 row) {
    return elements[col][row];
}

Map& Map::LoadFromFile(const string& path) {
    ifstream file(path, ifstream::in);

    Log::Write({"Loading map from ", path}, {"map"});
    int w = -1; int h = -1;
    int c = -1; int r = -1;
    Sint64 value; string line;

    SpriteIDLoader loader;
    while (file.good()) {
        getline(file, line);
        if (line.size() > 0 && line.at(0) != '#') {
            stringstream ss(line);

            if (w < 0 || h < 0) {
                ss >> w >> h;
                c = r = 0;
                Start(w, h);
            } else {
                c = 0;
                while (ss >> value) {
                    if (value >= 0) {
                        loader.value = value;
                        Set(c, r, loader.sprite);
                    }
                    if (++c >= w) break;
                }
                r++;
            }
            if (r >= h) break;
        }
    }
    file.close();
    return *this;
}

Uint16 Map::Cols() {
    return cols;
}

Uint16 Map::Rows() {
    return rows;
}

