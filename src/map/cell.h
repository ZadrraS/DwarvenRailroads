#ifndef DWARVENRR_MAP_CELL_H_
#define DWARVENRR_MAP_CELL_H_

#include "map/hex_coord.h"

#include <cstdlib>

namespace dwarvenrr 
{
    typedef size_t CellType;

    class Cell
    {
    public:
        Cell();
        Cell(const HexCoord<int>& position, CellType base_type = 0);
        ~Cell();

        CellType base_type() const;
        const HexCoord<int> &position() const;

    private:
        CellType base_type_;

        HexCoord<int> position_;

    };
}  // namespace dwarvenrr

#endif  // DWARVENRR_MAP_CELL_H_