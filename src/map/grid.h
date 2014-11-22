#ifndef DWARVENRR_MAP_GRID_H_
#define DWARVENRR_MAP_GRID_H_

#include <vector>

#include "map/cell.h"

namespace dwarvenrr 
{
    enum GridArrangementType
    {
        RECTANGLE,
        HEXAGON
    };

    typedef std::vector<Cell> CellContainer;

    class Grid
    {
    public:
        Grid();
        ~Grid();

        Cell &get_cell(const HexCoord<int> &coord);
        CellContainer &cells();
        const CellContainer &cells_const() const;

    private:
        CellContainer cells_; 

        GridArrangementType arrangement_type_;

    };
}  // namespace dwarvenrr

#endif  // DWARVENRR_MAP_GRID_H_