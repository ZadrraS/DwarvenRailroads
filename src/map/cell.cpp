#include "map/cell.h"

namespace dwarvenrr 
{
    Cell::Cell()
    {

    }
    
    Cell::Cell(const HexCoord<int>& position, size_t base_type) : base_type_(base_type), position_(position)
    {

    }

    Cell::~Cell() 
    {

    }

    size_t Cell::base_type() 
    {
        return base_type_;
    }
    
    const HexCoord<int> &Cell::position() const
    {
        return position_;
    }

}  // namespace dwarvenrr