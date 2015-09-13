#ifndef DWARVENRR_SYSTEMS_BASE_COMPONENT_MANAGER_H_
#define DWARVENRR_SYSTEMS_BASE_COMPONENT_MANAGER_H_

#include <exception>
#include <vector>
#include <unordered_map>

#include "systems/entity.h"
#include "systems/system_observer.h"

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
            std::swap(components_[*it], components_.back());
            components_.pop_back();

            id_pos_map_.erase(it);
        }
    }

    T &GetComponent(entity_id_t entity_id)
    {
        id_pos_map_t::iterator it = id_pos_map_.find(entity_id);
        if (it != id_pos_map_.end())
        {
            return components_[*it];
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
            return components_[*it];
        }
        else
        {
            throw std::out_of_range("Specified entity doesn't exist in manager.");
        }
    }

    void Register(SystemObserver<T> &observer)
    {
        observers_.push_back(&observer);
    }

    void Unregister(SystemObserver<T> &observer)
    {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), &observer), observers_.end());
    }

    void Notify(entity_id_t entity_id)
    {
        for (SystemObserver<T> *observer: observers_)
            observer->OnNotify(entity_id, GetComponent(entity_id));
    }

protected:
    std::vector<T> components_;
    id_pos_map_t id_pos_map_;

    std::vector<SystemObserver<T> *> observers_;
};

}  // namespace dwarvenrr

#endif  // DWARVENRR_SYSTEMS_BASE_COMPONENT_MANAGER_H_