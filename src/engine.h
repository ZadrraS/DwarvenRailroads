#ifndef DWARVERNRR_ENGINE_H_
#define DWARVERNRR_ENGINE_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace dwarvenrr
{

class Engine
{
public:
    Engine();
    ~Engine();

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

}  // namespace dwarvenrr

#endif  // DWARVERNRR_ENGINE_H_