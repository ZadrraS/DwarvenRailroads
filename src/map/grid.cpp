#include "map/grid.h"
#include "helpers/geometry.h"
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


    std::vector< Vector2<int> > Grid::GetNeighbours(const Vector2<int> &coord) const
    {
        std::vector< Vector2<int> > neighbours;
        std::vector< Vector2<int> > possible_neighbours;
        possible_neighbours.push_back(Vector2<int>(coord.x - 1, coord.y));
        possible_neighbours.push_back(Vector2<int>(coord.x, coord.y - 1));
        possible_neighbours.push_back(Vector2<int>(coord.x + 1, coord.y));
        possible_neighbours.push_back(Vector2<int>(coord.x, coord.y + 1));

        for (const Vector2<int> &neighbour: possible_neighbours)
        {
            if (IsPosValid(neighbour))
            {
                if (GetCell(neighbour).base_type() != 0)
                    neighbours.push_back(neighbour);
            }  
        }
        /*for (CellDirection dir = NORTH; dir <= NORTH_WEST; dir = CellDirection(dir + 1))
        {
            Vector2<int> neighbour = coord.GetNeighbour(dir);
            if (IsPosValid(neighbour))
            {
                if (GetCell(neighbour).base_type() != 0)
                    neighbours.push_back(neighbour);
            }
        }*/

        return neighbours;
    }

    bool Grid::IsPosValid(const Vector2<int> &coord) const
    {
        return coord.x >= 0 && coord.y >= 0 && (size_t)coord.x < width_ && (size_t)coord.y < height_;
    }

    double Grid::Distance(const Vector2<int> &coord1, const Vector2<int> &coord2) const
    {
        // Temporary
        return EuclideanDistance(coord1, coord2);
    }

    const Cell &Grid::GetCell(const Vector2<int> &coord) const
    {
        return cells_[coord.y * width_ + coord.x];
    }

    void Grid::Save(std::stringstream &buffer) const
    {

    }

    void Grid::Load(std::stringstream &buffer)
    {
        size_t width, height;
        buffer >> width >> height;
        width_ = width;
        height_ = height;
        cells_.resize(width * height);

        for (size_t y = 0; y < height; ++y)
        {
            for (size_t x = 0; x < width; ++x)
            {
                size_t type;
                buffer >> type;
                cells_[y * width + x] = Cell(Vector2<int>(x, y), type);
            }
        }
    }

}  // namespace dwarvenrr