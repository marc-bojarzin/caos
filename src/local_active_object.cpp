#include "caos/local_active_object.hpp"


namespace caos {

caos::local_active_object::local_active_object()
    : executor_(nullptr)
{
}

void caos::local_active_object::on_destroy()
{
    monitorable_active_object::on_destroy();
}



}
