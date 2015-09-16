#include "engine.h"

#include "map/array2d.h"
#include "helpers/vector_2.h"
#include "helpers/pathing.h"
#include "map/grid.h"
#include "rendering/map_renderer.h"
#include "resources/texture_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>

namespace dwarvenrr
{

Engine::Engine()
{

}

Engine::~Engine()
{

}

void Engine::PushState(BaseState *state)
{
    state_manager_.Push(state);
}

void Engine::Run()
{
    system_manager_.Init();

    std::chrono::duration<double> time_delta;
    while (!state_manager_.IsEmpty())
    {
        auto start_time = std::chrono::steady_clock::now();

        state_manager_.Update(time_delta.count()); //Placeholder for real time
        system_manager_.Update(time_delta.count());

        state_manager_.ExecutePops();
        state_manager_.ExecutePushes();

        auto end_time = std::chrono::steady_clock::now();
        time_delta = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);
        std::cout << "Time elapsed: " << time_delta.count() << std::endl;
    }
}

StateManager &Engine::GetStateManager()
{
    return state_manager_;
}

SystemManager &Engine::GetSystemManager()
{
    return system_manager_;
}

}  // namespace dwarvenrr