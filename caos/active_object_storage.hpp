#ifndef CAOS_ACTIVE_OBJECT_STORAGE_H
#define CAOS_ACTIVE_OBJECT_STORAGE_H

#include <new>
#include <atomic>
#include <cstddef>
#include <type_traits>

#include "caos/config.hpp"
#include "caos/forward.hpp"
#include "caos/active_object_control_block.hpp"
#include "caos/active_object_system.hpp"

namespace caos {

template<typename T>
class active_object_storage
{
    typedef active_object_storage self;

    static constexpr size_t pad_length()
    {
        return CAOS_CACHE_LINE_SIZE - sizeof(active_object_control_block);
    }

public:
    active_object_control_block control_block;

    char pad[pad_length()] = { 0 };

    union { T data_block; };

public:
    template<typename... Args>
    active_object_storage(active_object_id id, active_object_system* sys, Args&&... args)
        : control_block(id, sys, self::data_dtor, self::block_dtor)
    {
        static_assert(sizeof(active_object_control_block) < CAOS_CACHE_LINE_SIZE,
                      "active_object_control_block exceeds cache line");

        new (&data_block) T(std::forward<Args>(args)...);
    }

    ~active_object_storage()
    {
    }

    active_object_storage(const active_object_storage&) = delete;
    active_object_storage& operator = (const active_object_storage&) = delete;

private:
    static void data_dtor(abstract_active_object* obj)
    {
        obj->on_destroy();
        static_cast<T*>(obj)->~T();
    }

    static void block_dtor(active_object_control_block* control_block)
    {
        delete reinterpret_cast<active_object_storage*>(control_block);
    }
};

//--------------------------------------------------------------------------------------------------

template <typename T>
bool intrusive_ptr_upgrade_weak(active_object_storage<T>* obj)
{
    auto count = obj->control_block.strong_refs.load();
    while (count != 0)
    {
        if (obj->control_block.strong_refs.compare_exchange_weak(
                count, count + 1, std::memory_order_relaxed))
        {
            return true;
        }
    }
    return false;
}


template <typename T>
void intrusive_ptr_add_weak_ref(active_object_storage<T>* obj)
{
    obj->control_block.weak_refs.fetch_add(1, std::memory_order_relaxed);
}


template <typename T>
void intrusive_ptr_release_weak(active_object_storage<T>* obj)
{
    // destroy object if last weak pointer expires
    if (obj->control_block.weak_refs == 1 ||
        obj->control_block.weak_refs.fetch_sub(1, std::memory_order_acq_rel) == 1)
    {
        delete obj;
    }
}


template <class T>
void intrusive_ptr_add_ref(active_object_storage<T>* obj)
{
    obj->control_block.strong_refs.fetch_add(1, std::memory_order_relaxed);
}


template <class T>
void intrusive_ptr_release(active_object_storage<T>* obj)
{
    // release implicit weak pointer if the last strong ref expires
    // and destroy the data block
    if (obj->control_block.strong_refs.fetch_sub(1, std::memory_order_acq_rel) == 1)
    {
        obj->destroy_data();
        intrusive_ptr_relase_weak(obj);
    }
}

} // namespace caos

#endif // CAOS_ACTIVE_OBJECT_STORAGE_H
