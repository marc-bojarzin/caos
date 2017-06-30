#ifndef CAOS_FORWARD_HPP
#define CAOS_FORWARD_HPP

#include <cstdint>
#include <chrono>

#include "caos/intrusive_ptr.hpp"
#include "caos/weak_intrusive_pointer.hpp"

namespace caos {

class active_object_control_block;
class active_object_system;

using worker_id        = std::uint64_t;
using active_object_id = std::uint64_t;

using usec = std::chrono::microseconds;

using active_object_ptr = caos::intrusive_ptr<active_object_control_block>;
using active_object_ref = caos::weak_intrusive_ptr<active_object_control_block>;


}

#endif // CAOS_FORWARD_HPP
