#ifndef CAOS_ACTIVE_OBJECT_H
#define CAOS_ACTIVE_OBJECT_H

#include <functional>
#include "caos/local_active_object.hpp"

namespace caos {

/**
 * @brief The active_object class
 * This class should serve as the direct base class for all user defined active objects.
 */
class active_object : public caos::local_active_object
{
public:
    active_object();
};

} // namespace caos

#endif // CAOS_ACTIVE_OBJECT_H
