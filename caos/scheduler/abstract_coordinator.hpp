#ifndef CAOS_ABSTRACT_COORDINATOR_H
#define CAOS_ABSTRACT_COORDINATOR_H

#include "caos/active_object_system.hpp"

namespace caos {
namespace scheduler {

class abstract_coordinator
{
    active_object_system* home_system;

public:
    abstract_coordinator()
        : home_system(nullptr)
    {
    }
};

} // namespace scheduler
} // namespace caos

#endif // CAOS_ABSTRACT_COORDINATOR_H
