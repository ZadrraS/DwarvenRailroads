#ifndef DWARVENRR_SYSTEMS_BASE_COMPONENT_MANAGER_H_
#define DWARVENRR_SYSTEMS_BASE_COMPONENT_MANAGER_H_

#include <vector>
#include <unordered_map>

namespace dwarvenrr 
{

typedef unsigned int entity_id_t;

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
            // EXCEPTION!
        }
    }

    void RemoveComponent(entity_id_t entity_id)
    {
        std::unordered_map<entity_id_t, size_t>::iterator it = id_pos_map_.find(entity_id);
        if (it != id_pos_map_.end())
        {
            std::swap(components_[*it], components_.back());
            components_.pop_back();

            id_pos_map_.erase(it);
        }
    }

protected:
    std::vector<T> components_;
    std::unordered_map<entity_id_t, size_t> id_pos_map_;
};

}  // namespace dwarvenrr

#endif  // DWARVENRR_SYSTEMS_BASE_COMPONENT_MANAGER_H_