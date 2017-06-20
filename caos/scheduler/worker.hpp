#ifndef CAOS_WORKER_H
#define CAOS_WORKER_H

#include <thread>

#include "caos/forward.hpp"
#include "caos/execution_unit.hpp"
#include "caos/scheduler/coordinator.hpp"
#include "caos/active_object_system.hpp"

namespace caos {
namespace scheduler {

/**
 * @brief The poll_strategy struct
 */
class poll_strategy_phase
{
public:
    std::size_t attempts;         //!< attempts of aggressive polling without delay
    std::size_t step_size;        //!< 0 for the last phase of a strategy
    std::size_t steal_interval;   //!< try to steal every nth poll attempt
    usec        sleep_duration;   //!< sleep time between steal attempts
};

using poll_strategy = std::array<poll_strategy_phase, 3>;

/**
 * @brief The worker class
 */
class worker : public caos::execution_unit
{
    worker_id id_;
    std::thread thread_;
    poll_strategy strategy_;

public:
    explicit worker(worker_id id, const system_configuration& config);

    worker(const worker&) = delete;
    worker& operator = (const worker&) = delete;

    void start();

private:

    void run();
    job* dequeue();
    job* take_head();
    job* try_steal();
};


worker::worker(worker_id id, const system_configuration& config)
    : id_(id)
    , strategy_()
{
    strategy_[0].attempts       = config.worker_aggressive_poll_attempts;
    strategy_[0].step_size      = 1;
    strategy_[0].steal_interval = config.worker_aggressive_steal_interval;
    strategy_[0].sleep_duration = usec{0};

    strategy_[1].attempts       = config.worker_moderate_poll_attempts;
    strategy_[1].step_size      = 1;
    strategy_[1].steal_interval = config.worker_moderate_steal_interval;
    strategy_[1].sleep_duration = usec{config.worker_moderate_sleep_duration_us};

    strategy_[2].attempts       = 1;
    strategy_[2].step_size      = 0;
    strategy_[2].steal_interval = config.worker_relaxed_steal_interval;
    strategy_[2].sleep_duration = usec{config.worker_relaxed_sleep_duration_us};
}

void worker::start()
{
    thread_ = [this](void)->void
    {
        this->run();
    };
}

void worker::run()
{
    try
    {
        for(;;)
        {
            // dequeue next job
            // execute the job
            // if shutdown detected return
        }
    }
    catch(...)
    {
    }
}

job* worker::dequeue()
{
    void* job = nullptr;
    for (poll_strategy& phase : strategy_)
    {
        for (std::size_t i = 0; i < phase.attempts; i += phase.step_size)
        {
            // Poll our own queue
            job = take_head();
            if (job)
            {
                return job;
            }

            // Try to steal a job from another worker every N poll attempts
            if ((i % phase.steal_interval) == 0)
            {
                job = try_steal();
                if (job)
                {
                    return job;
                }
            }

            // Wait some time accroding to the current phase of the strategy.
            if (phase.sleep_duration.count() > 0)
            {
                std::this_thread::sleep_for(phase.sleep_duration);
            }
        }
    }

    // The last phase of the poll strategy guarantees to loop until a job has been dequeued.
    assert("unreachable");
    return nullptr;
}

job* worker::take_head()
{
    return nullptr;
}

job* worker::try_steal()
{
    return nullptr;
}

} // namespace scheduler
} // namespace caos

#endif // CAOS_WORKER_H
