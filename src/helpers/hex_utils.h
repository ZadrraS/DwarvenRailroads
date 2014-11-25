#ifndef DWARVENRR_HELPERS_HEX_UTILS_H_
#define DWARVENRR_HELPERS_HEX_UTILS_H_

#include "map/hex_coord.h"
#include "helpers/vector_2.h"

#include <cmath>
#include <iostream>
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
    HexCoord<T> GetHexCoords(const Vector2<T> &pixel_coord, T hex_size)
    {
        /*
        double q = 2.0 / 3.0 * pixel_coord.x / hex_size;
        double r = (-1.0 / 3.0 * pixel_coord.x + 1.0 / 3.0 * sqrt(3.0) * pixel_coord.y) / hex_size;

        HexCoord<T> roundedCoord = HexRound<T>(HexCoord<double>(q, r));

        double radius = hex_size;
        double height = sqrt(3.0) * radius;
        double z_proj = pixel_coord.y / height;
        double x_proj = 0.5 * (pixel_coord.x + sqrt(3.0) * pixel_coord.y) / height;
        double y_proj = -0.5 * (-pixel_coord.x + sqrt(3.0) * pixel_coord.y) / height;
        //double y_proj = -x_proj - z_proj;
        double norm = sqrt(x_proj * x_proj + y_proj * y_proj + z_proj * z_proj);
        roundedCoord = HexCoord<T>((T)(x_proj / norm), (T)(y_proj / norm), (T)(z_proj / norm));
        return roundedCoord;*/

        double radius = hex_size;
        double height = sqrt(3.0) * radius;
        double half_height = height / 2.0;


        Vector2<double> x_axis(0.5 * sqrt(3.0), 0.5);
        Vector2<double> y_axis(-0.5 * sqrt(3.0), 0.5);
        Vector2<double> z_axis(0.0, 1.0);

        double x_proj = 0.5 * (pixel_coord.x * sqrt(3.0) + pixel_coord.y);
        double y_proj = 0.5 * (pixel_coord.x * sqrt(3.0) - pixel_coord.y);
        double z_proj = pixel_coord.y;
        
        //y_proj = -z_proj - x_proj;

        

        Vector2<double> x_point(x_axis.x * x_proj, x_axis.y * x_proj);
        Vector2<double> y_point(y_axis.x * y_proj, y_axis.y * y_proj);
        Vector2<double> z_point(z_axis.x * z_proj, z_axis.y * z_proj);

        double axis_x_to_z_proj = -x_point.x * z_axis.x - x_point.y * z_axis.y;
        double axis_y_to_z_proj = y_point.x * z_axis.x + y_point.y * z_axis.y;
        

        double axis_z_to_x_proj = z_point.x * x_axis.x + z_point.y * x_axis.y;
        double z_adjustment = (axis_z_to_x_proj - x_proj);

        double axis_x_to_y_proj = x_point.x * y_axis.x + x_point.y * y_axis.y;
        double x_adjustment = (axis_x_to_y_proj - y_proj);

        double y_hex_pos = (y_proj + half_height) / height;
        double x_hex_pos = (x_proj + half_height) / height;
        double z_hex_pos = (z_proj + half_height + z_adjustment) / height;
        //x_hex_pos = x_hex_pos + y_hex_pos * 0.5;
        //z_hex_pos = z_hex_pos - y_hex_pos * 0.5;

        int y_coord = floor(y_hex_pos);
        int x_coord = floor(x_hex_pos);
        int z_coord = floor(z_hex_pos);
        //x_coord = x_hex_pos - x_coord
        std::cout << "Zadjust: " << z_adjustment / height << " xaxisproj: " << axis_x_to_z_proj / height << " yaxisproj: " << axis_y_to_z_proj / height << std::endl;
        std::cout << "PROJ: " << x_proj << " " << y_proj << " " << z_proj << " sum: " << x_proj + y_proj + z_proj << std::endl;
        std::cout << "Hexpos: " << x_hex_pos << " " << y_hex_pos << " " << z_hex_pos << " sum: " << x_hex_pos + y_hex_pos + z_hex_pos << std::endl;
        std::cout << "coord: " << x_coord << " " << y_coord << " " << z_coord << " sum: " << x_coord + y_coord + z_coord << std::endl;
        std::cout << std::endl;
        
        return HexCoord<T>((T)x_coord, (T)y_coord, (T)z_coord);
    }

    template<typename T>
    Vector2<int> GetPixelCoords(const HexCoord<T> &coord, T hex_size)
    {
        int x = (int)(hex_size * 3.0 / 2.0 * coord.q());
        int y = (int)(hex_size * sqrt(3.0) * (coord.r() + coord.q() / 2.0));

        return Vector2<int>(x, y);
    }

}  // namespace dwarvenrr

#endif  // DWARVENRR_HELPERS_HEX_UTILS_H_