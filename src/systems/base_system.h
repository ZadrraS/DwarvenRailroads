#ifndef DWARVENRR_SYSTEMS_BASE_SYSTEM_H_
#define DWARVENRR_SYSTEMS_BASE_SYSTEM_H_

#include <vector>
#include <unordered_map>

namespace dwarvenrr 
{

class BaseSystem
{
public:
    virtual void Update(double time_delta) = 0;
};

}  // namespace dwarvenrr

#endif  // DWARVENRR_SYSTEMS_BASE_SYSTEM_H_