#ifndef DWARVERNRR_ENGINE_H_
#define DWARVERNRR_ENGINE_H_

#include "states/state_manager.h"
#include "systems/system_manager.h"

namespace dwarvenrr
{

class Engine
{
public:
    Engine();
    ~Engine();

    void PushState(BaseState *state);
    void Run();

    StateManager &GetStateManager();
    SystemManager &GetSystemManager();

private:
    StateManager state_manager_;
    SystemManager system_manager_;
};

}  // namespace dwarvenrr

#endif  // DWARVERNRR_ENGINE_H_