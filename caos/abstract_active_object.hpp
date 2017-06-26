#ifndef CAOS_ABSTRACT_ACTIVE_OBJECT_H
#define CAOS_ABSTRACT_ACTIVE_OBJECT_H


namespace caos {

//--------------------------------------------------------------------------------------------------

class abstract_active_object
{
public:
    abstract_active_object();

    template<typename Callable, typename ... Args>
    inline void post(Callable func, Args&&... args)
    {
        std::function<void()> wrapped = std::bind(func, args...);
    }

    virtual void on_destroy();
};

//--------------------------------------------------------------------------------------------------



} // namespace caos

#endif // CAOS_ABSTRACT_ACTIVE_OBJECT_H
