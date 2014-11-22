#include "map/map.h"

namespace dwarvenrr 
{
    Map::Map()
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

    Map::~Map() 
    {

    }

    Cell &Map::get_cell(const HexCoord<int> &coord)
    {
        Vector2<int> odd_q_coord = coord.odd_q_offset();
        odd_q_coord.x += 3;
        odd_q_coord.y += 3;
        return cells_[odd_q_coord.y * 7 + odd_q_coord.x];
    }

    std::vector<Cell>::iterator Map::get_cell_begin()
    {
        return cells_.begin();
    }

    std::vector<Cell>::iterator Map::get_cell_end()
    {
        return cells_.end();
    }

}  // namespace dwarvenrr