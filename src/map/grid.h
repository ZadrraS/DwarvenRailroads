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

        CellContainer &cells();
        const CellContainer &cells_const() const;

        std::vector< Vector2<int> > GetNeighbours(const Vector2<int> &coord) const;
        bool IsPosValid(const Vector2<int> &coord) const;
        double Distance(const Vector2<int> &coord1, const Vector2<int> &coord2) const;
        const Cell &GetCell(const Vector2<int> &coord) const;

        void Save(std::stringstream &buffer) const;
        void Load(std::stringstream &buffer);

    private:
        CellContainer cells_;
        size_t width_;
        size_t height_;

        GridArrangementType arrangement_type_;

    };
}  // namespace dwarvenrr

#endif  // DWARVENRR_MAP_GRID_H_