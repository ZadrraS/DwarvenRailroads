#include "states/level_state.h"

#include "engine.h"

#include "states/state_manager.h"
#include "systems/system_manager.h"

namespace dwarvenrr
{

LevelState::LevelState(Engine &engine) : 
    BaseState(engine.GetStateManager(), engine.GetSystemManager())
{
    zoom_ = 1.0;
}

LevelState::~LevelState()
{

}

void LevelState::OnEnter()
{
    printf("Entering LevelState\n");

    test_texture_.loadFromFile("data/square_green.png");
    entity_id_t new_entity_id = system_manager_.AddEntity();
    RenderingComponent &rendering_component = 
        system_manager_.GetRenderingSystem().AddComponent(new_entity_id);

    rendering_component.sprite.setTexture(test_texture_);

    system_manager_.GetInputSystem().Register(*this);
    system_manager_.GetInputSystem().AddComponent(0);
}

void LevelState::Update(double time_delta)
{
    system_manager_.GetRenderingSystem().GetView().zoom(zoom_);
    zoom_ = 1.0;
}

void LevelState::OnClose()
{
    printf("Leaving LevelState\n");
}

void LevelState::Suspend()
{

}

void LevelState::Resume()
{

}


void LevelState::OnNotify(entity_id_t entity_id, InputComponent &component)
{
    (void)entity_id;
    printf("LevelState received an InputSystem update\n");
    if (component.event.type == sf::Event::KeyPressed)
    {
        sf::View &view = system_manager_.GetRenderingSystem().GetView();
        switch (component.event.key.code)
        {
            case sf::Keyboard::A:
                view.move(-1.0, 0.0);
            break;
            case sf::Keyboard::D:
                view.move(1.0, 0.0);
            break;
            case sf::Keyboard::W:
                view.move(0.0, -1.0); 
            break;
            case sf::Keyboard::S:
                view.move(0.0, 1.0);  
            break;
            case sf::Keyboard::E:
                view.rotate(0.1); 
            break;
            case sf::Keyboard::Q:
                view.rotate(-0.1); 
            break;
            case sf::Keyboard::Escape:
                state_manager_.SchedulePop();
            break;
            default:
            break;
        }
    }
    else if (component.event.type == sf::Event::MouseWheelMoved)
    {
        if (component.event.mouseWheel.delta > 0)
            zoom_ = 0.9;
        else if (component.event.mouseWheel.delta < 0)
            zoom_ = 1.1;
    }
    else if (component.event.type == sf::Event::Closed)
    {
        state_manager_.SchedulePop();
    }
}


}  // namespace dwarvenrr