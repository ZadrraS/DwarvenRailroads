#include "rendering/map_renderer.h"

#include "map/grid.h"
#include "resources/texture_manager.h"

#include <iostream>
#include <sstream>

namespace dwarvenrr
{
    MapRenderer::MapRenderer(TextureManager &texture_manager, const Grid &grid) : 
        grid_(grid), texture_manager_(texture_manager)
    {
        if (!font_.loadFromFile("data/sansation.ttf"))
        {
            std::cout << "Font ERROR" << std::endl;
        }

        cell_size_ = int(1.7455 * 32);

        origin_.x = 0;
        origin_.y = 0;
        for (CellContainer::const_iterator cell_it = grid_.cells_const().begin(); cell_it != grid_.cells_const().end(); ++cell_it)
        {
            sf::Sprite sprite;
            sprite.setTexture(texture_manager_.GetTexture(cell_it->base_type()));
            sprite.setScale(1.7455, 1.7455);
            sprite.setOrigin(texture_manager_.GetTexture(cell_it->base_type()).getSize().x  / 2, texture_manager_.GetTexture(cell_it->base_type()).getSize().y  / 2);
            //std::cout << "width: " << texture_manager_.GetTexture(cell_it->base_type()).getSize().x << std::endl;
            dwarvenrr::Vector2<int> cell_pos = dwarvenrr::Vector2<int>(cell_it->position().x * cell_size_, 
                                                                        cell_it->position().y * cell_size_);

            sprite.setPosition(cell_pos.x, cell_pos.y);
            sprites_.push_back(sprite);

            sf::Text text;

            // select the font
            text.setFont(font_); // font is a sf::Font

            // set the string to display
            std::stringstream ss;
            ss << "TROLO";
            text.setString(ss.str());

            // set the character size
            text.setCharacterSize(16); // in pixels, not points!
            text.setColor(sf::Color::Black);

            sf::FloatRect text_rect = text.getLocalBounds();
            text.setOrigin(text_rect.left + text_rect.width/2.0f, text_rect.top  + text_rect.height/2.0f);
            text.setPosition(cell_pos.x, cell_pos.y);
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
            if (cell_it->position() == highlighted_cell_coord_)
            {
                sprites_[i].setColor(sf::Color(0, 255, 0));
            }
            else
            {
                bool in_path = false;
                for (auto cell: path_)
                {
                    if (cell == cell_it->position())
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

        
    }

    void MapRenderer::HighlightCell(const sf::Vector2f &coord)
    {
        highlighted_cell_coord_ = Vector2<int>(coord.x * cell_size_, coord.y * cell_size_);
    }

    void MapRenderer::DrawPath(const std::vector< Vector2<int> > &path)
    {
        path_ = path;
    }

}  // namespace dwarvenrr