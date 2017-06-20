#ifndef CAOS_COORDINATOR_H
#define CAOS_COORDINATOR_H

#include <vector>
#include <memory>

#include "caos/scheduler/abstract_coordinator.hpp"
#include "caos/scheduler/worker.hpp"

namespace caos {
namespace scheduler {

class coordinator : public abstract_coordinator
{
    using super = abstract_coordinator;

    std::vector<std::unique_ptr<worker>> workers_;
    poll_strategy& strategy_;

public:
    coordinator();
    coordinator(const coordinator&) = delete;
    coordinator& operator = (const coordinator) = delete;
};

coordinator::coordinator()
    : super()
    , workers_()
    , strategy_(default_poll_strategy)
{
}

} // namespace scheduler
} // namespace caos

#endif // CAOS_COORDINATOR_H
