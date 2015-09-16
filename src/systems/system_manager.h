#ifndef DWARVENRR_SYSTEMS_SYSTEM_MANAGER_H_
#define DWARVENRR_SYSTEMS_SYSTEM_MANAGER_H_

#include <vector>

#include "systems/base_system.h"

#include "systems/rendering_system.h"
#include "systems/transform_system.h"
#include "systems/input_system.h"

namespace dwarvenrr 
{

class SystemManager
{
public:
    SystemManager();
    ~SystemManager();

    void Init();
    void Update(double time_delta);

    entity_id_t AddEntity();
    void RemoveEntity(entity_id_t entity_id);

    RenderingSystem &GetRenderingSystem();
    TransformSystem &GetTransformSystem();
    InputSystem &GetInputSystem();

private:
    entity_id_t latest_id_;
    std::vector<entity_id_t> entities_;

    RenderingSystem rendering_system_;
    TransformSystem transform_system_;
    InputSystem input_system_;
};

}  // dwarvenrr

#endif  // DWARVENRR_SYSTEMS_SYSTEM_MANAGER_H_