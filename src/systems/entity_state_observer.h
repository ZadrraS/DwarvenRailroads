#ifndef DWARVENRR_SYSTEMS_ENTITY_STATE_OBSERVER_H_
#define DWARVENRR_SYSTEMS_ENTITY_STATE_OBSERVER_H_

#include "systems/entity.h"

namespace dwarvenrr 
{

template <class T>
class EntityStateObserver
{
public:
    virtual void OnNotify(entity_id_t entity_id, T &component) = 0;
};

}  // namespace dwarvenrr

#endif  // DWARVENRR_SYSTEMS_ENTITY_STATE_OBSERVER_H_
