#include "rendering/map_renderer.h"

#include "map/grid.h"
#include "helpers/hex_utils.h"
#include "resources/texture_manager.h"

#include <iostream>
#include <sstream>

namespace dwarvenrr
{
    MapRenderer::MapRenderer(TextureManager &texture_manager, const Grid &grid) : texture_manager_(texture_manager), grid_(grid)
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
                sprites_[i].setColor(sf::Color(0, 255, 0));
            else
                sprites_[i].setColor(sf::Color(255, 255, 255));
            
            window.draw(sprites_[i]);
            window.draw(texts_[i]);
            i += 1;
        }
    }

    void MapRenderer::HighlightCell(const sf::Vector2f &coord)
    {
        highlighted_hex_coord_ = GetHexCoords(Vector2<int>(coord.x, coord.y), hex_size_);
    }
}  // namespace dwarvenrr