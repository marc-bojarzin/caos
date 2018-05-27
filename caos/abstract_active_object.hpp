#ifndef CAOS_ABSTRACT_ACTIVE_OBJECT_H
#define CAOS_ABSTRACT_ACTIVE_OBJECT_H

#include <functional>

#include "caos/forward.hpp"

namespace caos {

class active_object_control_block;

//--------------------------------------------------------------------------------------------------

class abstract_active_object
{
public:
    abstract_active_object();

    active_object_control_block* control_block() const;

    ~abstract_active_object();

    virtual void on_destroy();

    virtual void on_down();

    virtual void on_exit();

    active_object_id id() const noexcept;

    active_object_system& home_system() const noexcept;

protected:
    template<typename Callable, typename ... Args>
    inline void post(Callable func, Args&&... args)
    {
        //std::function<void()> wrapped = std::bind(func, args...);
    }
};

//--------------------------------------------------------------------------------------------------



} // namespace caos

#endif // CAOS_ABSTRACT_ACTIVE_OBJECT_H
