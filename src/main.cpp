#include "helpers/sfml_conversion.h"
#include "map/array2d.h"
#include "helpers/vector_2.h"

#include <SFML/Graphics.hpp>

#include <iostream>

int main()
{
  sf::RenderWindow window(sf::VideoMode(512, 512), "Test");

  sf::Texture texture;
  if (!texture.loadFromFile("data/hex.png"))
  {
    std::cout << "ERROP" << std::endl;
  }

  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setPosition(200.0, 100.0);
  sprite.setScale(0.25, 0.25);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
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
    window.draw(sprite);
    window.display();
  }

 // delete [] noise_image_data;

  return 0;
}