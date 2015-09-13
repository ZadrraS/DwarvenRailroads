#ifndef DWARVENRR_SYSTEMS_TRANSFORM_SYSTEM_H_
#define DWARVENRR_SYSTEMS_TRANSFORM_SYSTEM_H_

#include "systems/base_system.h"
#include "systems/base_component_manager.h"
#include "helpers/vector_2.h"

namespace dwarvenrr 
{

struct TransformComponent
{
    Vector2<float> position;
    double orientation;
};

class TransformSystem :  
    public BaseComponentManager<TransformComponent>, 
    public BaseSystem
{
public:
    TransformSystem();
    ~TransformSystem();

    void Update(double time_delta);

private:
};

}  // dwarvenrr

#endif  // DWARVENRR_SYSTEMS_TRANSFORM_SYSTEM_H_