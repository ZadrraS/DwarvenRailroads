#ifndef DWARVENRR_STATES_LEVEL_STATE_H_
#define DWARVENRR_STATES_LEVEL_STATE_H_

#include "states/base_state.h"

#include <SFML/Graphics.hpp>

namespace dwarvenrr 
{

class Engine;

class LevelState : public BaseState
{
public:
    LevelState(Engine &engine);
    ~LevelState();

    void OnEnter();
    void Update(double time_delta);
    void OnClose();

    void Suspend();
    void Resume();

    void OnNotify(entity_id_t entity_id, InputComponent &component);

private:
    // TEMPORARY STUFF
    double zoom_;
    sf::Texture test_texture_;
};

}  // namespace dwarvenrr

#endif  // DWARVENRR_STATES_LEVEL_STATE_H_