#ifndef DWARVENRR_SYSTEMS_INPUT_SYSTEM_H_
#define DWARVENRR_SYSTEMS_INPUT_SYSTEM_H_

#include "systems/base_system.h"
#include "systems/base_component_manager.h"

namespace dwarvenrr 
{

struct InputComponent
{
    sf::Event event;
};

class InputSystem :  
    public BaseSystem,
    public BaseComponentManager<InputComponent>
{
public:
    InputSystem(RenderingSystem &rendering_system);
    ~InputSystem();

    void Init();
    void Update(double time_delta);

private:
    RenderingSystem &rendering_system_;
};

}  // dwarvenrr

#endif  // DWARVENRR_SYSTEMS_INPUT_SYSTEM_H_