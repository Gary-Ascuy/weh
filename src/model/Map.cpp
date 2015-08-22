
#include "model/Map.h"

using namespace game::model;

Map::Map() {
}

Map::Map(uint16_t cols, uint16_t rows, uint8_t w, uint8_t h)
{
    Start(cols, rows);
}

Map& Map::Start(uint16_t cols, uint16_t rows) {
    this -> cols = cols;
    this -> rows = rows;

    elements.resize(cols);
    for (auto i = 0;i < cols;++i)
    {
        elements[i].resize(rows);
    }
    return *this;
}

Map& Map::Set(uint16_t col, uint16_t row, SpriteID resorce) {
    if (col >= 0 && col < cols && row >= 0 && row < rows) {
        elements[col][row] = resorce;
    }
    return *this;
}

SpriteID Map::Get(uint16_t col, uint16_t row) {
    return elements[col][row];
}

Map& Map::LoadFromFile(const string& path) {
    ifstream file(path, ifstream::in);

    iLogger(iINFO << iTAGS({"map"}) << "Loading map from gary" << path);
    int w = -1; int h = -1;
    int c = -1; int r = -1;
    int64_t value; string line;

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

uint16_t Map::Cols() {
    return cols;
}

uint16_t Map::Rows() {
    return rows;
}

