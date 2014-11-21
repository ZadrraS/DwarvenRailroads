#include "src/map/cell.h"

namespace dwarvenrr 
{
    Cell::Cell() {

    }

    Cell::~Cell() {

    }

    size_t Cell::get_ground_type() {
        return ground_type_;
    }

}  // namespace dwarvenrr