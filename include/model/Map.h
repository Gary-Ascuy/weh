
#ifndef MODEL__MAP_H_INCLUDED
#define MODEL__MAP_H_INCLUDED

#include <vector>
#include <iostream>

#include "model/Resource.h"

using namespace std;

namespace game { namespace model {

    /**
     * Manage information about the map
     */
    class IMapIterator {
        public:
            virtual bool operator()(Uint16 c, Uint16 r, const ResourceID& element) = 0;
    };

    class Map
    {
        private:
            Uint16 rows;
            Uint16 cols;
            vector< vector<ResourceID> > elements;

            Map& Start(Uint16 cols, Uint16 rows);

        public:
            Map(Uint16 cols, Uint16 rows, Uint8 w = 64, Uint8 h = 16);

            Map& Iterate(IMapIterator& iterator);
            Map& Set(Uint16 col, Uint16 row, ResourceID resorce);
            ResourceID& Get(Uint16 col, Uint16 row) const;

            Uint16 Cols();
            Uint16 Rows();
    };

}}

#endif // MODEL__MAP_H_INCLUDED
