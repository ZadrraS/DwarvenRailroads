#ifndef DWARVENRR_MAP_HEXOOORD_H_
#define DWARVENRR_MAP_HEXOOORD_H_

#include "helpers/vector_2.h"

#include <vector>

namespace dwarvenrr 
{
    enum HexDirection
    {
        NORTH,
        NORTH_EAST,
        SOUTH_EAST,
        SOUTH,
        SOUTH_WEST,
        NORTH_WEST        
    };

    template <typename T>
    class HexCoord
    {
    public:
        HexCoord(): q_(0), r_(0) { }
        HexCoord(T x, T y, T z): q_(x), r_(z) { (void)y; }
        HexCoord(T q, T r): q_(q), r_(r) { }
        HexCoord(T x, T y, bool odd) 
        {
            if (odd)
                set_odd_q_offset(Vector2<T>(x, y));
        }

        ~HexCoord() { }

        T q() const { return q_; }
        T r() const { return r_; }

        T x() const { return q_; }
        T y() const { return -q_ - r_; }
        T z() const { return r_; }

        bool operator==(const HexCoord<T> &coord) const
        {
            return q() == coord.q() and r() == coord.r();
        }

        bool operator!=(const HexCoord<T> &coord) const
        {
            return !(*this == coord);
        }

        void set_axial(T q, T r)
        {
            q_ = q;
            r_ = r;
        }

        void set_cube(T x, T y, T z)
        {
            q_ = x;
            r_ = z;
            (void)y;
        }

        Vector2<T> odd_q_offset() const
        {
            T x = this->x();
            T y = this->z() + (this->x() - (this->x() & 1)) / 2.0;
            return Vector2<T>(x, y);
        }

        void set_odd_q_offset(const Vector2<T> &odd_q_coord)
        {
            T z = odd_q_coord.y - (odd_q_coord.x - (odd_q_coord.x & 1)) / 2.0;
            set_cube(odd_q_coord.x, -odd_q_coord.x - z, z);
        }

        HexCoord<T> GetNeighbour(HexDirection direction) const
        {
            static const int neighbor_offsets_q[6] = {0, +1, +1, 0, -1, -1};
            static const int neighbor_offsets_r[6] = {-1, -1, 0, +1, +1, 0};
            return HexCoord<T>(q_ + neighbor_offsets_q[direction], r_ + neighbor_offsets_r[direction]);
        }

        std::vector< HexCoord<T> > GetNeighbours()
        {
            std::vector< HexCoord<T> > neighbours;
            neighbours.push_back(GetNeighbour(NORTH));
            neighbours.push_back(GetNeighbour(NORTH_EAST));
            neighbours.push_back(GetNeighbour(SOUTH_EAST));
            neighbours.push_back(GetNeighbour(SOUTH));
            neighbours.push_back(GetNeighbour(SOUTH_WEST));
            neighbours.push_back(GetNeighbour(NORTH_WEST));

            return neighbours;
        }

    private:
        T q_, r_;

    };
}  // namespace dwarvenrr

#endif  // DWARVENRR_MAP_HEXOOORD_H_