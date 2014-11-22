#ifndef DWARVENRR_MAP_MAP_H_
#define DWARVENRR_MAP_MAP_H_

#include <vector>

#include "map/cell.h"

namespace dwarvenrr 
{
    enum MapArrangementType
    {
        RECTANGLE,
        HEXAGON
    };

    class Map
    {
    public:
        Map();
        ~Map();

        Cell &get_cell(const HexCoord<int> &coord);
        std::vector<Cell>::iterator get_cell_begin();
        std::vector<Cell>::iterator get_cell_end();

    private:
        std::vector<Cell> cells_; 

        MapArrangementType arrangement_type_;

    };
}  // namespace dwarvenrr

#endif  // DWARVENRR_MAP_MAP_H_