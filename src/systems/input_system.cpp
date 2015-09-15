#include "systems/input_system.h"

namespace dwarvenrr
{

InputSystem::InputSystem(RenderingSystem &rendering_system) :
    rendering_system_(rendering_system)
{

}

InputSystem::~InputSystem()
{

}

void InputSystem::Init()
{
    
}

void InputSystem::Update(double time_delta)
{
    sf::Event event;
    while (rendering_system_.GetRenderWindow().pollEvent(event)) 
    {
        for (size_t i = 0; i < components_.size(); ++i)
            components_[i].event = event;

        for (id_pos_map_t::iterator it = id_pos_map.begin(); it != id_pos_map.end(); ++it)
            QueueNotification(it->first);
        
        RunPendingNotifications();
    }

    
}

}  // namespace dwarvenrr