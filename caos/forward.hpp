#ifndef CAOS_FORWARD_HPP
#define CAOS_FORWARD_HPP

#include <cstdint>
#include <chrono>

namespace caos {

using active_object_id = std::uint64_t;
using worker_id = std::uint64_t;
using usec = std::chrono::microseconds;

}

#endif // CAOS_FORWARD_HPP
