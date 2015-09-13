#include "engine.h"

#include <iostream>
#include "systems/rendering_system.h"
#include "systems/transform_system.h"
int main()
{
    dwarvenrr::RenderingSystem rendering_system;
    dwarvenrr::TransformSystem transform_system;

    rendering_system.Update(0.0);
    transform_system.Update(0.0);

    transform_system.AddComponent(0);
    transform_system.Register(rendering_system);
    transform_system.Update(0.0);
    //Engine engine;
    //std::cout << "Starting game..." << std::endl;
    //engine.Start();

    return 0;
}