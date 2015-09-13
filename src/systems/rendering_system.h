#ifndef DWARVENRR_SYSTEMS_RENDERING_SYSTEM_H_
#define DWARVENRR_SYSTEMS_RENDERING_SYSTEM_H_

#include <SFML/Graphics.hpp>

#include "systems/base_system.h"
#include "systems/base_component_manager.h"

namespace dwarvenrr 
{

struct RenderingComponent
{
    sf::Sprite sprite;
};

class RenderingSystem : 
    public BaseComponentManager<RenderingComponent>, 
    public BaseSystem
{
public:
    RenderingSystem();
    ~RenderingSystem();

    void Update(double time_delta);

private:
};

}  // dwarvenrr

#endif  // DWARVENRR_SYSTEMS_RENDERING_SYSTEM_H_