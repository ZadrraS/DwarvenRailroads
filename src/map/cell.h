#ifndef DWARVENRR_MAP_CELL_H_
#define DWARVENRR_MAP_CELL_H_

#include "map/hex_coord.h"

#include <cstdlib>

namespace dwarvenrr 
{
    class Cell
    {
    public:
        Cell();
        Cell(const HexCoord<int>& position, size_t base_type = 0);
        ~Cell();

        size_t base_type(); 
        const HexCoord<int> &position();

    private:
        size_t base_type_;

        HexCoord<int> position_;

    };
}  // namespace dwarvenrr

#endif  // DWARVENRR_MAP_CELL_H_