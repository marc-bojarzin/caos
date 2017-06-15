#ifndef CAOS_WORKER_H
#define CAOS_WORKER_H

#include "caos/execution_unit.hpp"

namespace caos {
namespace scheduler {

class worker : public execution_unit
{
public:
    worker();
};

} // namespace scheduler
} // namespace caos

#endif // CAOS_WORKER_H
