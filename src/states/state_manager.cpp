#include "states/state_manager.h"

#include "states/base_state.h"

namespace dwarvenrr
{

StateManager::StateManager()
{
    scheduled_pops_ = 0;
}

StateManager::~StateManager()
{

}

void StateManager::Update(double time_delta)
{
    if (!states_.empty())
        states_.back()->Update(time_delta);
}

void StateManager::Push(BaseState *state)
{
    states_.push_back(state);
    state->OnEnter();
}

void StateManager::Pop()
{
    if (!states_.empty())
    {
        BaseState *state = states_.back();
        states_.pop_back();
        state->OnClose();
    }
}

void StateManager::SchedulePush(BaseState *state)
{
    scheduled_pushes_.push_back(state);
}

void StateManager::SchedulePop()
{
    scheduled_pops_ += 1;
}

void StateManager::ExecutePushes()
{
    for (BaseState *state: scheduled_pushes_)
        Push(state);

    scheduled_pushes_.clear();
}

void StateManager::ExecutePops()
{
    for (size_t i = 0; i < scheduled_pops_; ++i)
        Pop();

    scheduled_pops_ = 0;
}

bool StateManager::IsEmpty()
{
    return states_.empty();
}

}  // namespace dwarvenrr