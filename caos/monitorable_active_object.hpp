#ifndef CAOS_MONITORABLE_ACTIVE_OBJECT_H
#define CAOS_MONITORABLE_ACTIVE_OBJECT_H

#include "caos/abstract_active_object.hpp"

namespace caos {

//--------------------------------------------------------------------------------------------------

class monitorable_active_object : public abstract_active_object
{
public:
    monitorable_active_object()
    {
    }

protected:
    virtual void on_cleanup();
};

//--------------------------------------------------------------------------------------------------


} // namespace caos

#endif // CAOS_MONITORABLE_ACTIVE_OBJECT_H
