#ifndef DWARVENRR_RESOURCES_TEXTURE_MANAGER_H_
#define DWARVENRR_RESOURCES_TEXTURE_MANAGER_H_

#include "map/cell.h"

#include <vector>
#include <sstream>

#include <SFML/Graphics.hpp>

namespace dwarvenrr 
{
    class TextureManager
    {
    public:
        TextureManager();
        ~TextureManager();

        sf::Texture &GetTexture(CellType type);
        void Load(std::stringstream &buffer);

    private:
        std::vector< std::pair<CellType, std::string> > texture_cell_bindings_;
        std::map<CellType, sf::Texture> textures_;

    };
}  // namespace dwarvenrr

#endif  // DWARVENRR_RESOURCES_TEXTURE_MANAGER_H_