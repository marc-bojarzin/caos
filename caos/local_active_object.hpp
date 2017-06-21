#ifndef CAOS_LOCAL_ACTIVE_OBJECT_H
#define CAOS_LOCAL_ACTIVE_OBJECT_H

#include "caos/monitorable_active_object.hpp"
#include "caos/execution_unit.hpp"

namespace caos {

//--------------------------------------------------------------------------------------------------

class local_active_object : public monitorable_active_object
{
    execution_unit* executor_;

public:
    local_active_object();
    void on_destroy() override;
};

//--------------------------------------------------------------------------------------------------

} // namespace caos

#endif // CAOS_LOCAL_ACTIVE_OBJECT_H
