#ifndef DWARVENRR_RENDERING_MAP_RENDERER_H_
#define DWARVENRR_RENDERING_MAP_RENDERER_H_

#include <SFML/Graphics.hpp>

#include "map/hex_coord.h"

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
        void DrawPath(const std::vector< HexCoord<int> > &path);
        HexCoord<int> GetHexFromScreen(const sf::Vector2f &coord);

    private:
        const Grid &grid_;

        std::vector<sf::Sprite> sprites_;
        std::vector<sf::Text> texts_;
        TextureManager &texture_manager_;
        sf::Font font_;

        sf::Vector2i origin_;

        int hex_size_;
        HexCoord<int> highlighted_hex_coord_;
        std::vector< HexCoord<int> > path_;
    };

}  // namespace dwarvenrr

#endif  // DWARVENRR_RENDERING_MAP_RENDERER_H_