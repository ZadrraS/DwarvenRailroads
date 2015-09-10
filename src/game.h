#ifndef DWARVERNRR_GAME_
#define DWARVENRR_GAME_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();
    ~Game();

    void Start();

private:
    enum State
    {
        UNINITIALIZED,
        PAUSED,
        RUNNING,
        EXITING
    };

    bool IsDone();
    void MainLoop();

    State state_;
    sf::RenderWindow render_window_;
};

#endif  // DWARVENRR_GAME_