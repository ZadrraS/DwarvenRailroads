#ifndef DWARVENRR_SYSTEMS_BASE_COMPONENT_MANAGER_H_
#define DWARVENRR_SYSTEMS_BASE_COMPONENT_MANAGER_H_

#include <exception>
#include <vector>
#include <unordered_map>

#include "systems/entity.h"
#include "systems/entity_state_observer.h"

namespace dwarvenrr 
{

typedef std::unordered_map<entity_id_t, size_t> id_pos_map_t;

template <class T>
class BaseComponentManager
{
public:
    virtual ~BaseComponentManager()
    {

    }

    T &AddComponent(entity_id_t entity_id)
    {
        if (id_pos_map_.find(entity_id) == id_pos_map_.end())
        {
            components_.push_back(T());
            id_pos_map_[entity_id] = components_.size() - 1;

            return components_.back();
        }
        else
        {
            throw std::out_of_range("Specified entity id already in manager.");
        }
    }

    void RemoveComponent(entity_id_t entity_id)
    {
        id_pos_map_t::iterator it = id_pos_map_.find(entity_id);
        if (it != id_pos_map_.end())
        {
            std::swap(components_[it->second], components_.back());
            components_.pop_back();

            id_pos_map_.erase(it);
        }
    }

    T &GetComponent(entity_id_t entity_id)
    {
        id_pos_map_t::iterator it = id_pos_map_.find(entity_id);
        if (it != id_pos_map_.end())
        {
            return components_[it->second];
        }
        else
        {
            throw std::out_of_range("Specified entity doesn't exist in manager.");
        }
    }

    const T &GetComponent(entity_id_t entity_id) const
    {
        id_pos_map_t::iterator it = id_pos_map_.find(entity_id);
        if (it != id_pos_map_.end())
        {
            return components_[it->second];
        }
        else
        {
            throw std::out_of_range("Specified entity doesn't exist in manager.");
        }
    }

    void Register(EntityStateObserver<T> &observer)
    {
        observers_.push_back(&observer);
    }

    void Unregister(EntityStateObserver<T> &observer)
    {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), &observer), observers_.end());
    }

    void Notify(entity_id_t entity_id)
    {
        for (EntityStateObserver<T> *observer: observers_)
            observer->OnNotify(entity_id, GetComponent(entity_id));
    }

    void QueueNotification(entity_id_t entity_id)
    {
        pending_notifications_.push_back(entity_id);
    }

    void RunPendingNotifications()
    {
        for (entity_id_t entity_id: pending_notifications_)
        {
            Notify(entity_id);
}
        pending_notifications_.clear();
    }

protected:
    std::vector<T> components_;
    id_pos_map_t id_pos_map_;

    std::vector<EntityStateObserver<T> *> observers_;
    std::vector<entity_id_t> pending_notifications_;
};

}  // namespace dwarvenrr

#endif  // DWARVENRR_SYSTEMS_BASE_COMPONENT_MANAGER_H_