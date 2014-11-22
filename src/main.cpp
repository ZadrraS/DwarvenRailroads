#include "map/array2d.h"
#include "helpers/vector_2.h"
#include "helpers/hex_utils.h"
#include "map/hex_coord.h"
#include "map/map.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>

int main()
{
    sf::Vector2i resolution(1024, 1024);
    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Test");

    sf::Font font;
    if (!font.loadFromFile("data/sansation.ttf"))
    {
        std::cout << "Font ERROR" << std::endl;
    }

    sf::Texture texture;
    if (!texture.loadFromFile("data/hex.png"))
    {
        std::cout << "ERROP" << std::endl;
    }
    sf::Vector2<unsigned int> textureSize = texture.getSize();
    std::cout << "texsize: " << textureSize.x << " " << textureSize.y << std::endl;
    int hexSize = 0.2 * textureSize.x / 2;

    std::vector<sf::Sprite> sprites;
    std::vector<sf::Text> texts;

    dwarvenrr::Map map;
    for (std::vector<dwarvenrr::Cell>::iterator cellIt = map.get_cell_begin(); cellIt != map.get_cell_end(); ++cellIt)
    {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setScale(0.2, 0.2);
        sprite.setOrigin(textureSize.x  / 2, textureSize.y  / 2);
        
        dwarvenrr::Vector2<int> hexPos = dwarvenrr::GetPixelCoords(cellIt->position(), int(0.2 * textureSize.x / 2));

        sprite.setPosition(hexPos.x + 512, hexPos.y + 512);
        sprites.push_back(sprite);

        sf::Text text;

        // select the font
        text.setFont(font); // font is a sf::Font

        // set the string to display
        std::stringstream ss;
        ss << cellIt->position().q();
        ss << "    ";
        ss << cellIt->position().r();
        text.setString(ss.str());

        // set the character size
        text.setCharacterSize(16); // in pixels, not points!
        
        //text.setOrigin(textureSize.x * 0.2 / 2, textureSize.y * 0.2 / 2);
        text.setColor(sf::Color::Black);

        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        text.setPosition(hexPos.x + 512, hexPos.y + 512);
        texts.push_back(text);
    }
    /*
    for (int y = -3; y <= 3; ++y)
    {
        for (int x = -3; x <= 3; ++x)
        {
            dwarvenrr::HexCoord<int> hexCoord(x, y);
            if (dwarvenrr::HexDistance(hexCoord, dwarvenrr::HexCoord<int>(0, 0)) > 3)
                continue;

            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setScale(0.2, 0.2);
            sprite.setOrigin(textureSize.x  / 2, textureSize.y  / 2);
            
            dwarvenrr::Vector2<int> hexPos = dwarvenrr::GetPixelCoords(hexCoord, int(0.2 * textureSize.x / 2));

            sprite.setPosition(hexPos.x + 512, hexPos.y + 512);
            sprites.push_back(sprite);

            sf::Text text;

            // select the font
            text.setFont(font); // font is a sf::Font

            // set the string to display
            std::stringstream ss;
            ss << x;
            ss << "    ";
            ss << y;
            text.setString(ss.str());

            // set the character size
            text.setCharacterSize(16); // in pixels, not points!
            
            //text.setOrigin(textureSize.x * 0.2 / 2, textureSize.y * 0.2 / 2);
            text.setColor(sf::Color::Black);

            sf::FloatRect textRect = text.getLocalBounds();
            text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
            text.setPosition(hexPos.x + 512, hexPos.y + 512);
            texts.push_back(text);
        }
    }
    */

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {

            }
        }

        window.clear(sf::Color::White);
        // DRAW STUFF
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        localPosition.x -= resolution.x / 2;
        localPosition.y -= resolution.y / 2;

        dwarvenrr::HexCoord<int> mouseHexCoord = dwarvenrr::GetHexCoords(dwarvenrr::Vector2<int>(localPosition.x, localPosition.y), hexSize);
        size_t i = 0;
        for (std::vector<dwarvenrr::Cell>::iterator cellIt = map.get_cell_begin(); cellIt != map.get_cell_end(); ++cellIt)
        {
            if (cellIt->position() == mouseHexCoord)
                sprites[i].setColor(sf::Color(0, 255, 0));
            else
                sprites[i].setColor(sf::Color(255, 255, 255));
            window.draw(sprites[i]);
            window.draw(texts[i]);
            i += 1;
        }
        /*
        for (size_t i = 0; i < sprites.size(); ++i)
        {
            if 
            sprite.setColor(sf::Color(0, 255, 0));
            window.draw(sprites[i]);
            window.draw(texts[i]);
        }*/
        window.display();
    }

    // delete [] noise_image_data;
    return 0;
}