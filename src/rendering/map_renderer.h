#ifndef DWARVENRR_RENDERING_MAP_RENDERER_H_
#define DWARVENRR_RENDERING_MAP_RENDERER_H_

#include <SFML/Graphics.hpp>

#include "helpers/vector_2.h"

namespace dwarvenrr 
{
    class Grid;
    class TextureManager;
    
    class MapRenderer
    {
    public:
        MapRenderer(TextureManager &texture_manager, const Grid &grid);
        ~MapRenderer();

        void Draw(sf::RenderWindow &window);

        void HighlightCell(const sf::Vector2f &coord);
        void DrawPath(const std::vector< Vector2<int> > &path);

    private:
        const Grid &grid_;

        std::vector<sf::Sprite> sprites_;
        std::vector<sf::Text> texts_;
        TextureManager &texture_manager_;
        sf::Font font_;

        sf::Vector2i origin_;

        int cell_size_;
        Vector2<int> highlighted_cell_coord_;
        std::vector< Vector2<int> > path_;
    };

}  // namespace dwarvenrr

#endif  // DWARVENRR_RENDERING_MAP_RENDERER_H_