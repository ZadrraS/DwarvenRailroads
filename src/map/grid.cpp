#include "map/grid.h"

#include "helpers/hex_utils.h"
#include <iostream>
namespace dwarvenrr 
{
    Grid::Grid()
    {
       
    }

    Grid::~Grid() 
    {

    }

    CellContainer &Grid::cells()
    {
        return cells_;
    }

    const CellContainer &Grid::cells_const() const
    {
        return cells_;
    }


    std::vector< HexCoord<int> > Grid::GetNeighbours(const HexCoord<int> &coord) const
    {
        std::vector< HexCoord<int> > neighbours;
        for (HexDirection dir = NORTH; dir <= NORTH_WEST; dir = HexDirection(dir + 1))
        {
            HexCoord<int> neighbour = coord.GetNeighbour(dir);
            if (IsPosValid(neighbour))
            {
                if (GetCell(neighbour).base_type() != 0)
                    neighbours.push_back(neighbour);
            }
        }

        return neighbours;
    }

    bool Grid::IsPosValid(const HexCoord<int> &coord) const
    {
        int x_center = width_ / 2;
        int y_center = height_ / 2;
        Vector2<int> offset = coord.odd_q_offset();
        int x = offset.x + x_center;
        int y = offset.y + y_center;
        return x >= 0 && y >= 0 && (size_t)x < width_ && (size_t)y < height_;
    }

    double Grid::Distance(const HexCoord<int> &coord1, const HexCoord<int> &coord2) const
    {
        // Temporary
        return HexDistance(coord1, coord2);
    }

    const Cell &Grid::GetCell(const HexCoord<int> &coord) const
    {
        int x_center = width_ / 2;
        int y_center = height_ / 2;
        Vector2<int> offset = coord.odd_q_offset();
        int x = offset.x + x_center;
        int y = offset.y + y_center;
        return cells_[y * width_ + x];
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
            width_ = width;
            height_ = height;
            size_t x_center = width / 2;
            size_t y_center = height / 2;
            cells_.resize(width * height);

            for (size_t y = 0; y < height; ++y)
            {
                for (size_t x = 0; x < width; ++x)
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