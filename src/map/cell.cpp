#include "map/cell.h"

namespace dwarvenrr 
{
    Cell::Cell()
    {

    }
    
    Cell::Cell(const Vector2<int>& position, CellType base_type) : base_type_(base_type), position_(position)
    {

    }

    Cell::~Cell() 
    {

    }

    CellType Cell::base_type() const
    {
        return base_type_;
    }
    
    const Vector2<int> &Cell::position() const
    {
        return position_;
    }

}  // namespace dwarvenrr