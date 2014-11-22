#ifndef DWARVENRR_MAP_HEXOOORD_H_
#define DWARVENRR_MAP_HEXOOORD_H_

#include "helpers/vector_2.h"

namespace dwarvenrr 
{
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

    private:
        T q_, r_;

    };
}  // namespace dwarvenrr

#endif  // DWARVENRR_MAP_HEXOOORD_H_