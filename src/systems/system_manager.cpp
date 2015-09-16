#include "systems/system_manager.h"

namespace dwarvenrr
{

SystemManager::SystemManager() : input_system_(rendering_system_)
{
    latest_id_ = 0;
}

SystemManager::~SystemManager()
{

}

void SystemManager::Init()
{
    rendering_system_.Init();
    transform_system_.Init();
    input_system_.Init();
}

void SystemManager::Update(double time_delta)
{
    rendering_system_.Update(time_delta);
    transform_system_.Update(time_delta);
    input_system_.Update(time_delta);
}

entity_id_t SystemManager::AddEntity()
{
    latest_id_++;
    entities_.push_back(latest_id_);
    
    return latest_id_;
}

void SystemManager::RemoveEntity(entity_id_t entity_id)
{
    rendering_system_.RemoveComponent(entity_id);
    transform_system_.RemoveComponent(entity_id);
    input_system_.RemoveComponent(entity_id);
}

RenderingSystem &SystemManager::GetRenderingSystem()
{
    return rendering_system_;
}

TransformSystem &SystemManager::GetTransformSystem()
{
    return transform_system_;
}

InputSystem &SystemManager::GetInputSystem()
{
    return input_system_;
}


}  // namespace dwarvenrr