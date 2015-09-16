#include "systems/rendering_system.h"

namespace dwarvenrr
{

RenderingSystem::RenderingSystem()
{

}

RenderingSystem::~RenderingSystem()
{

}

void RenderingSystem::Init()
{
    sf::Vector2i resolution(1024, 1024);
    render_window_.create(sf::VideoMode(resolution.x, resolution.y), "Test window");
    view_.setViewport(sf::FloatRect(0.0, 0.0, 1024.0, 1024.0));
    render_window_.setView(view_);
}

void RenderingSystem::Update(double time_delta)
{
    render_window_.clear(sf::Color::Black);
    for (RenderingComponent &rendering_component: components_)
    {
        render_window_.draw(rendering_component.sprite);
    }
    render_window_.display();
}

void RenderingSystem::OnNotify(entity_id_t entity_id, TransformComponent &component)
{
    printf("Notification received about a rendering component!\n");
}


sf::RenderWindow &RenderingSystem::GetRenderWindow()
{
    return render_window_;
}

sf::View &RenderingSystem::GetView()
{
    return view_;
}


}  // namespace dwarvenrr