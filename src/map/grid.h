#ifndef DWARVENRR_MAP_GRID_H_
#define DWARVENRR_MAP_GRID_H_

#include "map/cell.h"

#include <vector>
#include <sstream>

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

        void Save(std::stringstream &buffer) const;
        void Load(std::stringstream &buffer);

    private:
        CellContainer cells_; 

        GridArrangementType arrangement_type_;

    };
}  // namespace dwarvenrr

#endif  // DWARVENRR_MAP_GRID_H_