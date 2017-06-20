#ifndef CAOS_ACTIVE_OBJECT_CONTROL_BLOCK_H
#define CAOS_ACTIVE_OBJECT_CONTROL_BLOCK_H

#include "caos/config.hpp"
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
    active_object_id id;
    active_object_system* home_system;
    data_destructor data_dtor;
    block_destructor block_dtor;

public:
    active_object_control_block(active_object_id id, active_object_system* sys,
                                data_destructor data_dtor, block_destructor block_dtor);

    active_object_control_block(const active_object_control_block&) = delete;
    active_object_control_block& operator = (const active_object_control_block&) = delete;

    /// Returns a pointer to the actual active object.
    inline abstract_active_object* get();

    /// Returns a pointer to the control block of an active object.
    static active_object_control_block* from(const abstract_actor* ptr);

};

//--------------------------------------------------------------------------------------------------

active_object_control_block::active_object_control_block(active_object_id id,
                                                         active_object_system* sys,
                                                         active_object_control_block::data_destructor data_dtor,
                                                         active_object_control_block::block_destructor block_dtor)
    : strong_refs(1)
    , weak_refs(1)
    , id(id)
    , home_system(sys)
    , data_dtor(data_destructor)
    , block_dtor(block_destructor)
{
}

abstract_active_object* active_object_control_block::get()
{
    return reinterpret_cast<abstract_active_object*>(
                reinterpret_cast<intptr_t>(this) + CAOS_CACHE_LINE_SIZE);
}

active_object_control_block* active_object_control_block::from(const abstract_actor* ptr)
{
    return reinterpret_cast<actor_control_block*>(
                reinterpret_cast<intptr_t>(ptr) - CAOS_CACHE_LINE_SIZE);
}

} // namespace caos

#endif // CAOS_ACTIVE_OBJECT_CONTROL_BLOCK_H
