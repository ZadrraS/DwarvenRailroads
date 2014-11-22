#include "map/grid.h"

namespace dwarvenrr 
{
    Grid::Grid()
    {
        cells_.resize(49);
        arrangement_type_ = RECTANGLE;
        for (int x = 0; x <= 6; ++x)
        {
            for (int y = 0; y <= 6; ++y)
            {
                //Nothing yet
                cells_[y * 7 + x] = Cell(HexCoord<int>(x - 3, y - 3, true));
            }
        }
    }

    Grid::~Grid() 
    {

    }

    Cell &Grid::get_cell(const HexCoord<int> &coord)
    {
        Vector2<int> odd_q_coord = coord.odd_q_offset();
        odd_q_coord.x += 3;
        odd_q_coord.y += 3;
        return cells_[odd_q_coord.y * 7 + odd_q_coord.x];
    }

    CellContainer &Grid::cells()
    {
        return cells_;
    }

    const CellContainer &Grid::cells_const() const
    {
        return cells_;
    }

}  // namespace dwarvenrr