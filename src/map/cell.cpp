#include "map/cell.h"

namespace dwarvenrr 
{
    Cell::Cell()
    {

    }
    
    Cell::Cell(const HexCoord<int>& position, CellType base_type) : base_type_(base_type), position_(position)
    {

    }

    Cell::~Cell() 
    {

    }

    CellType Cell::base_type() const
    {
        return base_type_;
    }
    
    const HexCoord<int> &Cell::position() const
    {
        return position_;
    }

}  // namespace dwarvenrr