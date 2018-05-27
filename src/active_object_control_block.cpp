#include "caos/active_object_control_block.hpp"

namespace caos {

bool intrusive_ptr_upgrade_weak(active_object_control_block* x)
{
    size_t count = x->strong_refs.load();
    while (count != 0)
    {
        if (x->strong_refs.compare_exchange_weak(count, count + 1, std::memory_order_relaxed))
        {
            return true;
        }
    }
    return false;
}

void intrusive_ptr_release_weak(active_object_control_block* x)
{
    // destroy object if last weak pointer expires
    if (x->weak_refs == 1 or x->weak_refs.fetch_sub(1, std::memory_order_acq_rel) == 1)
    {
        x->block_dtor(x);
    }
}

void intrusive_ptr_release(active_object_control_block* x)
{
    // release implicit weak pointer if the last strong ref expires and destroy the data block
    if (x->strong_refs.fetch_sub(1, std::memory_order_acq_rel) == 1)
    {
        x->data_dtor(x->get());
        intrusive_ptr_release_weak(x);
    }
}

bool operator == (const active_object_ptr& lhs, const abstract_active_object* rhs)
{
    return lhs.get() == active_object_control_block::from(rhs);
}

bool operator == (const abstract_active_object* lhs, const active_object_ptr& rhs)
{
    return active_object_control_block::from(lhs) == rhs.get();
}


} // namespace caos
