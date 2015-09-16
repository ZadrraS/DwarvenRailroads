#ifndef DWARVENRR_SYSTEMS_RENDERING_SYSTEM_H_
#define DWARVENRR_SYSTEMS_RENDERING_SYSTEM_H_

#include <SFML/Graphics.hpp>

#include "systems/base_system.h"
#include "systems/base_component_manager.h"
#include "systems/entity_state_observer.h"
#include "systems/transform_system.h"

namespace dwarvenrr 
{

struct RenderingComponent
{
    sf::Sprite sprite;
};

class RenderingSystem : 
    public BaseSystem,
    public BaseComponentManager<RenderingComponent>,
    public EntityStateObserver<TransformComponent>
{
public:
    RenderingSystem();
    ~RenderingSystem();

    void Init();
    void Update(double time_delta);
    void OnNotify(entity_id_t entity_id, TransformComponent &component);

    sf::RenderWindow &GetRenderWindow();
    sf::View &GetView();

private:
    sf::RenderWindow render_window_;
    sf::View view_;

};

}  // dwarvenrr

#endif  // DWARVENRR_SYSTEMS_RENDERING_SYSTEM_H_