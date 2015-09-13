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

void RenderingSystem::OnNotify(entity_id_t entity_id, TransformComponent &component)
{
    printf("Notification received about a rendering component!\n");
}

}  // namespace dwarvenrr