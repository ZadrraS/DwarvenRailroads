#include "rendering/map_renderer.h"

#include "map/grid.h"
#include "helpers/hex_utils.h"
#include "resources/texture_manager.h"

#include <iostream>
#include <sstream>

namespace dwarvenrr
{
    MapRenderer::MapRenderer(TextureManager &texture_manager, const Grid &grid) : grid_(grid), texture_manager_(texture_manager)
    {
        if (!font_.loadFromFile("data/sansation.ttf"))
        {
            std::cout << "Font ERROR" << std::endl;
        }

        hex_size_ = int(1.7455 * 32);

        origin_.x = 0;
        origin_.y = 0;
        for (CellContainer::const_iterator cell_it = grid_.cells_const().begin(); cell_it != grid_.cells_const().end(); ++cell_it)
        {
            sf::Sprite sprite;
            sprite.setTexture(texture_manager_.GetTexture(cell_it->base_type()));
            sprite.setScale(1.7455, 1.7455);
            sprite.setOrigin(texture_manager_.GetTexture(cell_it->base_type()).getSize().x  / 2, texture_manager_.GetTexture(cell_it->base_type()).getSize().y  / 2);
            //std::cout << "width: " << texture_manager_.GetTexture(cell_it->base_type()).getSize().x << std::endl;
            dwarvenrr::Vector2<int> hex_pos = dwarvenrr::GetPixelCoords(cell_it->position(), hex_size_);

            sprite.setPosition(hex_pos.x, hex_pos.y);
            sprites_.push_back(sprite);

            sf::Text text;

            // select the font
            text.setFont(font_); // font is a sf::Font

            // set the string to display
            std::stringstream ss;
            ss << cell_it->position().q();
            ss << "    ";
            ss << cell_it->position().r();
            text.setString(ss.str());

            // set the character size
            text.setCharacterSize(16); // in pixels, not points!
            text.setColor(sf::Color::Black);

            sf::FloatRect text_rect = text.getLocalBounds();
            text.setOrigin(text_rect.left + text_rect.width/2.0f, text_rect.top  + text_rect.height/2.0f);
            text.setPosition(hex_pos.x, hex_pos.y);
            texts_.push_back(text);
        }
    }

    MapRenderer::~MapRenderer()
    {

    }

    void MapRenderer::Draw(sf::RenderWindow &window)
    {
        size_t i = 0;
        for (CellContainer::const_iterator cell_it = grid_.cells_const().begin(); cell_it != grid_.cells_const().end(); ++cell_it)
        {
            if (cell_it->position() == highlighted_hex_coord_)
            {
                sprites_[i].setColor(sf::Color(0, 255, 0));
            }
            else
            {
                bool in_path = false;
                for (auto hex: path_)
                {
                    if (hex == cell_it->position())
                    {
                        in_path = true;
                        sprites_[i].setColor(sf::Color(0, 0, 255));
                        break;
                    }
                }
                if (!in_path)
                    sprites_[i].setColor(sf::Color(255, 255, 255));
            }
            
            window.draw(sprites_[i]);
            window.draw(texts_[i]);
            i += 1;
        }

        Vector2<double> x_axis(0.5 * sqrt(3.0), 0.5);
        Vector2<double> y_axis(-0.5 * sqrt(3.0), 0.5);
        Vector2<double> z_axis(0.0, 1.0);
        double radius = hex_size_;
        double height = sqrt(3.0) * radius;
        double z_proj = pixel_coord.y / height;
        double x_proj = 0.5 * (pixel_coord.x * sqrt(3.0) + pixel_coord.y) / height;
        double y_proj = 0.5 * (-pixel_coord.x * sqrt(3.0) + pixel_coord.y) / height;
        //double y_proj = -x_proj - z_proj;
        //std::cout << x_proj << " " << y_proj << " " << z_proj << " sum: " << x_proj + y_proj + z_proj << std::endl;
        //roundedCoord = HexCoord<int>((int)(x_proj), (int)(y_proj), (int)(z_proj));

        sf::Vertex line_x_axis[] =
        {
            sf::Vertex(sf::Vector2f(x_axis.x * 1000, x_axis.y * 1000), sf::Color(255, 0, 0)),
            sf::Vertex(sf::Vector2f(-x_axis.x * 1000, -x_axis.y * 1000), sf::Color(255, 0, 0))
        };
        sf::Vertex line_y_axis[] =
        {
            sf::Vertex(sf::Vector2f(y_axis.x * 1000, y_axis.y * 1000), sf::Color(0, 255, 0)),
            sf::Vertex(sf::Vector2f(-y_axis.x * 1000, -y_axis.y * 1000), sf::Color(0, 255, 0))
        };
        sf::Vertex line_z_axis[] =
        {
            sf::Vertex(sf::Vector2f(z_axis.x * 1000, z_axis.y * 1000), sf::Color(0, 0, 255)),
            sf::Vertex(sf::Vector2f(-z_axis.x * 1000, -z_axis.y * 1000), sf::Color(0, 0, 255))
        };

        window.draw(line_x_axis, 2, sf::Lines);
        window.draw(line_z_axis, 2, sf::Lines);
        window.draw(line_y_axis, 2, sf::Lines);

        x_proj *= height;
        y_proj *= height;
        z_proj *= height;
        sf::CircleShape circle_x_axis(5);
        circle_x_axis.setFillColor(sf::Color(255, 0, 0));
        circle_x_axis.setPosition(sf::Vector2f(x_proj * x_axis.x, x_proj * x_axis.y));
        circle_x_axis.setOrigin(sf::Vector2f(5, 5));
        sf::CircleShape circle_y_axis(5);
        circle_y_axis.setFillColor(sf::Color(0, 255, 0));
        circle_y_axis.setPosition(sf::Vector2f(y_proj * y_axis.x, y_proj * y_axis.y));
        circle_y_axis.setOrigin(sf::Vector2f(5, 5));
        sf::CircleShape circle_z_axis(5);
        circle_z_axis.setFillColor(sf::Color(0, 0, 255));
        circle_z_axis.setPosition(sf::Vector2f(z_proj * z_axis.x, z_proj * z_axis.y));
        circle_z_axis.setOrigin(sf::Vector2f(5, 5));

        window.draw(circle_x_axis);
        window.draw(circle_y_axis);
        window.draw(circle_z_axis);
    }

    void MapRenderer::HighlightCell(const sf::Vector2f &coord)
    {
        pixel_coord = coord;
        highlighted_hex_coord_ = GetHexCoords(Vector2<int>(coord.x, coord.y), hex_size_);
    }

    void MapRenderer::DrawPath(const std::vector< HexCoord<int> > &path)
    {
        path_ = path;
    }

    HexCoord<int> MapRenderer::GetHexFromScreen(const sf::Vector2f &coord)
    {
        return GetHexCoords(Vector2<int>(coord.x, coord.y), hex_size_);
    }

}  // namespace dwarvenrr