#ifndef DWARVENRR_MAP_CELL_H_
#define DWARVENRR_MAP_CELL_H_

#include "helpers/vector_2.h"

#include <cstdlib>

namespace dwarvenrr 
{

    enum EdgeDirection
    {
        FORWARD_LEFT,
        FORWARD,
        FORWARD_RIGHT,
        BACKWARD_RIGHT,
        BACKWARD,
        BACKWARD_LEFT
    };

    typedef size_t CellType;

    class Cell
    {
    public:
        Cell();
        Cell(const Vector2<int>& position, CellType base_type = 0);
        ~Cell();

        CellType base_type() const;
        const Vector2<int> &position() const;

    private:
        CellType base_type_;

        Vector2<int> position_;

    };

}  // namespace dwarvenrr

#endif  // DWARVENRR_MAP_CELL_H_