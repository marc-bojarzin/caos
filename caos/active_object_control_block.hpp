#ifndef CAOS_ACTIVE_OBJECT_CONTROL_BLOCK_H
#define CAOS_ACTIVE_OBJECT_CONTROL_BLOCK_H

#include <atomic>

#include "caos/config.hpp"
#include "caos/forward.hpp"
#include "caos/active_object_system.hpp"
#include "caos/abstract_active_object.hpp"
#include "caos/intrusive_ptr.hpp"
#include "caos/weak_intrusive_pointer.hpp"

namespace caos {

//--------------------------------------------------------------------------------------------------

class active_object_control_block
{
public:
    using data_destructor = void (*)(abstract_active_object*);
    using block_destructor = void (*)(active_object_control_block*);

    std::atomic_size_t strong_refs;
    std::atomic_size_t weak_refs;
    active_object_id object_id;
    active_object_system* home_system;
    data_destructor data_dtor;
    block_destructor block_dtor;

public:
    active_object_control_block(active_object_id id, active_object_system* sys,
                                data_destructor data_dtor, block_destructor block_dtor)
        : strong_refs(1)
        , weak_refs(1)
        , object_id(id)
        , home_system(sys)
        , data_dtor(data_dtor)
        , block_dtor(block_dtor)
    {
    }

    active_object_control_block(const active_object_control_block&) = delete;
    active_object_control_block& operator = (const active_object_control_block&) = delete;

    /// Returns a pointer to the actual active object.
    inline abstract_active_object* get()
    {
        return reinterpret_cast<abstract_active_object*>(
                    reinterpret_cast<intptr_t>(this) + CAOS_CACHE_LINE_SIZE);
    }

    /// Returns a pointer to the control block of an active object.
    static active_object_control_block* from(const abstract_active_object* ptr)
    {
        return reinterpret_cast<active_object_control_block*>(
                    reinterpret_cast<intptr_t>(ptr) - CAOS_CACHE_LINE_SIZE);
    }

    inline active_object_id id() const noexcept
    {
        return object_id;
    }

};

//--------------------------------------------------------------------------------------------------

bool intrusive_ptr_upgrade_weak(active_object_control_block* x);

inline void intrusive_ptr_add_weak_ref(active_object_control_block* x)
{
    x->weak_refs.fetch_add(1, std::memory_order_relaxed);
}

void intrusive_ptr_release_weak(active_object_control_block* x);

inline void intrusive_ptr_add_ref(active_object_control_block* x)
{
    x->strong_refs.fetch_add(1, std::memory_order_relaxed);
}

void intrusive_ptr_release(active_object_control_block* x);

bool operator == (const active_object_ptr&, const abstract_active_object*);

bool operator == (const abstract_active_object*, const active_object_ptr&);

inline bool operator != (const active_object_ptr& x, const abstract_active_object* y)
{
    return !(x == y);
}

inline bool operator != (const abstract_active_object* x, const active_object_ptr& y)
{
    return !(x == y);
}

} // namespace caos

//--------------------------------------------------------------------------------------------------

// allow actor pointers to be used in hash maps
namespace std {

template <>
struct hash<caos::active_object_ptr>
{
    inline size_t operator () (const caos::active_object_ptr& ptr) const
    {
        return ptr ? static_cast<size_t>(ptr->id()) : 0;
    }
};

template <>
struct hash<caos::active_object_ref>
{
    inline size_t operator () (const caos::active_object_ref& ref) const
    {
        return ref ? static_cast<size_t>(ref->id()) : 0;
    }
};

} // namespace std

//--------------------------------------------------------------------------------------------------

#endif // CAOS_ACTIVE_OBJECT_CONTROL_BLOCK_H
