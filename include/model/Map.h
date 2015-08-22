
#ifndef MODEL__MAP_H_INCLUDED
#define MODEL__MAP_H_INCLUDED

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#include "model/Resource.h"
#include "ilog/Logger.h"

using namespace std;

namespace game { namespace model {

    class Map
    {
        public:
            Map();
            Map(uint16_t cols, uint16_t rows, uint8_t w = 64, uint8_t h = 16);

            Map& Set(uint16_t col, uint16_t row, SpriteID id);
            SpriteID Get(uint16_t col, uint16_t row);
            Map& LoadFromFile(const string& path);

            uint16_t Cols();
            uint16_t Rows();

            Map& Start(uint16_t cols, uint16_t rows);

        protected:
            vector< vector<SpriteID> > elements;

            uint16_t rows;
            uint16_t cols;
    };

}}

#endif // MODEL__MAP_H_INCLUDED
