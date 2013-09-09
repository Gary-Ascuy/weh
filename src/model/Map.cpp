
#include "model/Map.h"

using namespace game::model;

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

Map& Map::Iterate(IMapIterator& iterator) {
    for (Uint16 c = 0;c < cols;++c) {
        for (Uint16 r = 0;r < rows;++r) {
            iterator(c, r, elements[c][r]);
        }
    }
    return *this;
}

Map& Map::Set(Uint16 col, Uint16 row, ResourceID resorce) {
    if (col >= 0 && col < cols && row >= 0 && row < rows) {
        this -> elements[col][row] = resorce;
    } else {
        cout << "Unvalid" << endl;
    }
}

Uint16 Map::Cols() {
    return cols;
}

Uint16 Map::Rows() {
    return rows;
}

