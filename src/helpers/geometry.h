#ifndef DWARVENRR_HELPERS_GEOMETRY_H_
#define DWARVENRR_HELPERS_GEOMETRY_H_

#include "helpers/vector_2.h"

#include <cmath>

namespace dwarvenrr 
{

template <class T>
inline double EuclideanDistance(const Vector2<T> &vec1, const Vector2<T> &vec2)
{
   return sqrt((double)(vec1.x - vec2.x) * (vec1.x - vec2.x) + (vec1.y - vec2.y) * (vec1.y - vec2.y));
}

}  // namespace dwarvenrr

#endif  // DWARVENRR_HELPERS_GEOMETRY_H_