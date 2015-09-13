#include "systems/rendering_system.h"

namespace dwarvenrr
{

RenderingSystem::RenderingSystem()
{

}

RenderingSystem::~RenderingSystem()
{

}

void RenderingSystem::Update(double time_delta)
{
    printf("I am a RENDERING system, beep boop!\n");
}

}  // namespace dwarvenrr