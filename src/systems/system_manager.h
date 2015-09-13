#ifndef DWARVENRR_SYSTEMS_SYSTEM_MANAGER_H_
#define DWARVENRR_SYSTEMS_SYSTEM_MANAGER_H_

#include "systems/base_system.h"

namespace dwarvenrr 
{

class SystemManager
{
public:
    SystemManager();
    ~SystemManager();

    void Update(double time_delta);

private:
};

}  // dwarvenrr

#endif  // DWARVENRR_SYSTEMS_SYSTEM_MANAGER_H_