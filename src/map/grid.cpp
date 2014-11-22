#include "map/grid.h"

namespace dwarvenrr 
{
    Grid::Grid()
    {
       
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

    void Grid::Save(std::stringstream &buffer) const
    {
        buffer << arrangement_type_ << "\n";
        if (arrangement_type_ == RECTANGLE)
        {

        }
    }

    void Grid::Load(std::stringstream &buffer)
    {
        size_t arr_type;
        buffer >> arr_type;
        arrangement_type_ = (GridArrangementType)arr_type;
        if (arrangement_type_ == RECTANGLE)
        {
            size_t width, height;
            buffer >> width >> height;
            size_t x_center = width / 2;
            size_t y_center = height / 2;
            cells_.resize(width * height);
            for (size_t x = 0; x < width; ++x)
            {
                for (size_t y = 0; y < height; ++y)
                {
                    size_t type;
                    buffer >> type;
                    cells_[y * width + x] = Cell(HexCoord<int>((int)x - x_center, (int)y - y_center, true), type);
                }
            }
        }
        else if (arrangement_type_ == HEXAGON)
        {
            size_t radius;
            buffer >> radius;
        }
    }

}  // namespace dwarvenrr