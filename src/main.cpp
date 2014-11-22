#include "map/array2d.h"
#include "helpers/vector_2.h"
#include "helpers/hex_utils.h"
#include "map/hex_coord.h"
#include "map/grid.h"
#include "rendering/map_renderer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <sstream>

int main()
{
    sf::Vector2i resolution(1024, 1024);
    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Test");

    dwarvenrr::Grid grid;
    dwarvenrr::MapRenderer map_renderer(grid);

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            view.move(-1.0, 0.0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            view.move(1.0, 0.0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            view.move(0.0, -1.0);            
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            view.move(0.0, 1.0);            
        }
        view.zoom(zoom);
        zoom = 1.0;
        window.setView(view);

        sf::Vector2i local_position = sf::Mouse::getPosition(window);
        sf::Vector2f world_position = window.mapPixelToCoords(local_position);
        local_position.x = local_position.x + view.getCenter().x - view.getSize().x;
        local_position.y = local_position.y + view.getCenter().y - view.getSize().y;

        map_renderer.HighlightCell(world_position);

        window.clear(sf::Color::White);
        // DRAW STUFF
        map_renderer.Draw(window);
        window.display();
    }

    return 0;
}