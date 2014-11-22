#ifndef DWARVENRR_HELPERS_HEX_UTILS_H_
#define DWARVENRR_HELPERS_HEX_UTILS_H_

#include "map/hex_coord.h"
#include "helpers/vector_2.h"

#include <cmath>

namespace dwarvenrr 
{
    template<typename T>
    T HexDistance(const HexCoord<T> &coord1, const HexCoord<T> &coord2)
    {
        return (abs(coord1.x() - coord2.x()) + abs(coord1.y() - coord2.y()) + abs(coord1.z() - coord2.z())) / 2;
    }

    template<typename T>
    HexCoord<T> HexRound(const HexCoord<double> &coord)
    {
        double rx = round(coord.x());
        double ry = round(coord.y());
        double rz = round(coord.z());

        double x_diff = abs(rx - coord.x());
        double y_diff = abs(ry - coord.y());
        double z_diff = abs(rz - coord.z());

        if (x_diff > y_diff && x_diff > z_diff)
            rx = -ry - rz;
        else if (y_diff > z_diff)
            ry = -rx - rz;
        else
            rz = -rx - ry;

        return HexCoord<T>((T)rx, (T)ry, (T)rz);
    }
    template<typename T>
    HexCoord<T> GetHexCoords(const Vector2<T> &pixel_coord, T hexSize)
    {
        double q = 2.0 / 3.0 * pixel_coord.x / hexSize;
        double r = (-1.0 / 3.0 * pixel_coord.x + 1.0 / 3.0 * sqrt(3.0) * pixel_coord.y) / hexSize;

        HexCoord<T> roundedCoord = HexRound<T>(HexCoord<double>(q, r));
        return roundedCoord;
    }

    template<typename T>
    Vector2<int> GetPixelCoords(const HexCoord<T> &coord, T hexSize)
    {
        int x = (int)(hexSize * 3.0 / 2.0 * coord.q());
        int y = (int)(hexSize * sqrt(3.0) * (coord.r() + coord.q() / 2.0));

        return Vector2<int>(x, y);
    }

    

}  // namespace dwarvenrr

#endif  // DWARVENRR_HELPERS_HEX_UTILS_H_