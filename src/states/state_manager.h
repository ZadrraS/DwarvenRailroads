#ifndef DWARVENRR_STATES_STATE_MANAGER_H_
#define DWARVENRR_STATES_STATE_MANAGER_H_

#include <vector>
#include <cstddef>

namespace dwarvenrr 
{

class BaseState;

class StateManager
{
public:
    StateManager();
    ~StateManager();

    void Update(double time_delta);

    void Push(BaseState *state);
    void Pop();

    void SchedulePush(BaseState *state);
    void SchedulePop();

    void ExecutePushes();
    void ExecutePops();

    bool IsEmpty();

private:
    std::vector<BaseState *> states_;

    size_t scheduled_pops_;
    std::vector<BaseState *> scheduled_pushes_;
};

}  // namespace dwarvenrr

#endif  // DWARVENRR_STATES_STATE_MANAGER_H_