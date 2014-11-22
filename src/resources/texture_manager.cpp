#include "resources/texture_manager.h"

#include <iostream>

namespace dwarvenrr
{

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

sf::Texture &TextureManager::GetTexture(CellType type)
{
    if (textures_.find(type) != textures_.end())
    {
        return textures_[type];
    }
    else
    {
        return textures_[0];
    }
}

void TextureManager::Load(std::stringstream &buffer)
{
    while (!buffer.eof())
    {
        CellType type;
        std::string texture_file_name;
        buffer >> type >> texture_file_name;
        if (texture_file_name == "")
            continue;
        
        texture_cell_bindings_.push_back(std::pair<CellType, std::string>(type, texture_file_name));
        sf::Texture texture;
        if (!texture.loadFromFile("data/" + texture_file_name))
        {
            std::cout << "ERROP" << std::endl;
        }
        textures_[type] = texture;
    }
}

}  // namespace dwarvenrr