#ifndef CAOS_ABSTRACT_ACTIVE_OBJECT_H
#define CAOS_ABSTRACT_ACTIVE_OBJECT_H


namespace caos {

class abstract_active_object
{
public:
    abstract_active_object();
    virtual void on_destroy() { }
};

} // namespace caos

#endif // CAOS_ABSTRACT_ACTIVE_OBJECT_H
