#ifndef SYSTEM_CONFIGURATION_H
#define SYSTEM_CONFIGURATION_H

#include <cstdint>

namespace caos {

struct system_configuration
{
    std::size_t worker_aggressive_poll_attempts;
    std::size_t worker_aggressive_steal_interval;
    std::size_t worker_moderate_poll_attempts;
    std::size_t worker_moderate_steal_interval;
    std::size_t worker_moderate_sleep_duration_us;
    std::size_t worker_relaxed_steal_interval;
    std::size_t worker_relaxed_sleep_duration_us;

    system_configuration();
};

//--------------------------------------------------------------------------------------------------

system_configuration::system_configuration()
{
    worker_aggressive_poll_attempts  =  100;
    worker_aggressive_steal_interval  =  10;
    worker_moderate_poll_attempts  =  500;
    worker_moderate_steal_interval  =  5;
    worker_moderate_sleep_duration_us  =  50;
    worker_relaxed_steal_interval  =  1;
    worker_relaxed_sleep_duration_us  =  10000;  // 10ms
}

} // namespace caos

#endif // SYSTEM_CONFIGURATION_H
