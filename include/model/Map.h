
#ifndef MODEL__MAP_H_INCLUDED
#define MODEL__MAP_H_INCLUDED

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#include "model/Resource.h"
#include "model/Log.h"

using namespace std;

namespace game { namespace model {

    class Map
    {
        public:
            Map();
            Map(Uint16 cols, Uint16 rows, Uint8 w = 64, Uint8 h = 16);

            Map& Set(Uint16 col, Uint16 row, SpriteID id);
            SpriteID Get(Uint16 col, Uint16 row);
            Map& LoadFromFile(const string& path);

            Uint16 Cols();
            Uint16 Rows();

            Map& Start(Uint16 cols, Uint16 rows);

        protected:
            vector< vector<SpriteID> > elements;

            Uint16 rows;
            Uint16 cols;
    };

}}

#endif // MODEL__MAP_H_INCLUDED
