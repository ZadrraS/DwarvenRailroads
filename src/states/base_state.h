#ifndef DWARVENRR_STATES_BASE_STATE_H_
#define DWARVENRR_STATES_BASE_STATE_H_

#include "systems/entity_state_observer.h"
#include "systems/input_system.h"

namespace dwarvenrr 
{

class StateManager;
class SystemManager;

class BaseState : public EntityStateObserver<InputComponent>
{
public:
    BaseState(StateManager &state_manager, SystemManager &system_manager) : 
        state_manager_(state_manager), system_manager_(system_manager)
    {

    }

    virtual void OnEnter() = 0;
    virtual void Update(double time_delta) = 0;
    virtual void OnClose() = 0;

    virtual void Suspend() = 0;
    virtual void Resume() = 0;

protected:
    StateManager &state_manager_;
    SystemManager &system_manager_;
};

}  // namespace dwarvenrr

#endif  // DWARVENRR_STATES_BASE_STATE_H_