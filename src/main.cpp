#include "engine.h"
#include "states/level_state.h"

#include <iostream>

int main()
{
    dwarvenrr::Engine engine;
    dwarvenrr::LevelState level_state(engine);
    engine.PushState(&level_state);
    
    std::cout << "Starting game..." << std::endl;
    engine.Run();

    return 0;
}