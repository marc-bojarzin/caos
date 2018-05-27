#ifndef STRONG_PTR_H
#define STRONG_PTR_H

#include "caos/abstract_active_object.hpp"

namespace caos {

template<typename T>
class strong_ptr
{
public:
    typedef T*       pointer;
    typedef const T* const_pointer;
    typedef T        reference;
    typedef const T  const_reference;

    strong_ptr(abstract_active_object* ptr)
    {

    }
};

} // namespace caos

#endif // STRONG_PTR_H
