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

        cell_size_ = 64;

        origin_.x = 0;
        origin_.y = 0;
        for (CellContainer::const_iterator cell_it = grid_.cells_const().begin(); cell_it != grid_.cells_const().end(); ++cell_it)
        {
            sf::Sprite sprite;
            sprite.setTexture(texture_manager_.GetTexture(cell_it->base_type()));
            sprite.setScale(1.0, 1.0);
            sprite.setOrigin(0, 0);
            dwarvenrr::Vector2<int> cell_pos = dwarvenrr::Vector2<int>(cell_it->position().x * cell_size_, 
                                                                        cell_it->position().y * cell_size_);

            sprite.setPosition(cell_pos.x, cell_pos.y);
            sprites_.push_back(sprite);

            sf::Text text;

            // select the font
            text.setFont(font_); // font is a sf::Font

            // set the string to display
            //std::stringstream ss;
            //ss << "TROLO";
            //text.setString(ss.str());

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
                sprites_[i].setColor(sf::Color(192, 192, 192));
            }
            else
            {
                bool in_path = false;
                for (auto cell: path_)
                {
                    if (cell == cell_it->position())
                    {
                        in_path = true;
                        sprites_[i].setColor(sf::Color(128, 128, 128));
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

    void MapRenderer::HighlightCell(const Vector2<int> &coord)
    {
        highlighted_cell_coord_ = coord;
    }

    void MapRenderer::DrawPath(const std::vector< Vector2<int> > &path)
    {
        path_ = path;
    }

    Vector2<int> MapRenderer::GetCellCoordFromScreen(const Vector2<int> &coord)
    {
        return Vector2<int>((int)(coord.x / cell_size_), (int)(coord.y / cell_size_));
    }

}  // namespace dwarvenrr