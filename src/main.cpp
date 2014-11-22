#include "map/array2d.h"
#include "helpers/vector_2.h"
#include "helpers/hex_utils.h"
#include "map/hex_coord.h"
#include "map/grid.h"
#include "rendering/map_renderer.h"
#include "resources/texture_manager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <sstream>
#include <fstream>

int main()
{
    sf::Vector2i resolution(1024, 1024);
    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Test");

    dwarvenrr::Grid grid;

    std::ifstream map_file("data/testmap.txt");
    if (map_file)
    {
        std::stringstream buffer;
        buffer << map_file.rdbuf();

        map_file.close();
        grid.Load(buffer);
    }
    else
    {
        std::cout << "RESOURCE ERROR" << std::endl;
    }

    dwarvenrr::TextureManager texture_manager;
    std::ifstream texture_file("data/testresourceassignment.txt");
    if (texture_file)
    {
        std::stringstream buffer;
        buffer << texture_file.rdbuf();

        texture_file.close();
        texture_manager.Load(buffer);
    }
    else
    {
        std::cout << "RESOURCE ERROR" << std::endl;
    }
    
    dwarvenrr::MapRenderer map_renderer(texture_manager, grid);

    sf::View view(sf::FloatRect(-512.0, -512.0, 1024.0, 1024.0));
    double zoom = 1.0;
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
            else if (event.type == sf::Event::MouseWheelMoved)
            {
                if (event.mouseWheel.delta > 0)
                    zoom = 0.9;
                else if (event.mouseWheel.delta < 0)
                    zoom = 1.1;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            view.move(-1.0, 0.0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            view.move(1.0, 0.0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            view.move(0.0, -1.0);            
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            view.move(0.0, 1.0);            
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            view.rotate(0.1); 
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            view.rotate(-0.1); 
        }

        view.zoom(zoom);
        zoom = 1.0;
        window.setView(view);

        sf::Vector2i local_position = sf::Mouse::getPosition(window);
        sf::Vector2f world_position = window.mapPixelToCoords(local_position);
        local_position.x = local_position.x + view.getCenter().x - view.getSize().x;
        local_position.y = local_position.y + view.getCenter().y - view.getSize().y;

        map_renderer.HighlightCell(world_position);

        window.clear(sf::Color::Black);
        // DRAW STUFF
        map_renderer.Draw(window);
        window.display();
    }

    return 0;
}