#include "caos/abstract_active_object.hpp"
#include "caos/active_object_control_block.hpp"

namespace caos {


abstract_active_object::abstract_active_object()
{
}

active_object_control_block* abstract_active_object::control_block() const
{
    return active_object_control_block::from(this);
}

abstract_active_object::~abstract_active_object()
{
}

void abstract_active_object::on_destroy()
{
}

void abstract_active_object::on_down()
{
}

void abstract_active_object::on_exit()
{
}

active_object_id abstract_active_object::id() const noexcept
{
    return active_object_control_block::from(this)->id();
}

active_object_system& abstract_active_object::home_system() const noexcept
{
    return *(active_object_control_block::from(this)->home_system);
}


}
