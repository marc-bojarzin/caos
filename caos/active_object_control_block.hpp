#ifndef CAOS_ACTIVE_OBJECT_CONTROL_BLOCK_H
#define CAOS_ACTIVE_OBJECT_CONTROL_BLOCK_H

#include "caos/forward.hpp"
#include "caos/active_object_system.hpp"
#include "caos/abstract_active_object.hpp"

namespace caos {

//--------------------------------------------------------------------------------------------------

class active_object_control_block
{
public:
    using data_destructor = void (*)(abstract_active_object*);
    using block_destructor = void (*)(active_object_control_block*);

    size_t strong_refs;
    size_t weak_refs;
    active_object_id aid;
    active_object_system* home_system;
    data_destructor data_dtor;
    block_destructor block_dtor;

public:
    active_object_control_block(active_object_id id, active_object_system* sys,
                        data_destructor data_dtor,
                        block_destructor block_dtor)
        : strong_refs(1)
        , weak_refs(1)
        , aid(id)
        , home_system(sys)
    {
    }

    active_object_control_block(const active_object_control_block&) = delete;
    active_object_control_block& operator = (const active_object_control_block&) = delete;

    inline active_object_id aoid() const noexcept
    {
        return aoid;
    }
};

//--------------------------------------------------------------------------------------------------



} // namespace caos

#endif // CAOS_ACTIVE_OBJECT_CONTROL_BLOCK_H
