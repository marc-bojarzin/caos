
#include <string>
#include <iostream>

#include "caos/local_active_object.hpp"
#include "caos/intrusive_ptr.hpp"
#include "caos/active_object_storage.hpp"

using namespace std;

//--------------------------------------------------------------------------------------------------

class simple_active_object : public caos::local_active_object
{
public:
    simple_active_object();
    void on_destroy() override;
};

//--------------------------------------------------------------------------------------------------

simple_active_object::simple_active_object()
{
}

void simple_active_object::on_destroy()
{
    local_active_object::on_destroy();
}

//--------------------------------------------------------------------------------------------------

int main(int argc, char ** argv)
{
    using active_object_hnd = caos::intrusive_ptr<caos::abstract_active_object>;

    caos::active_object_storage<simple_active_object> storage(0, nullptr);

    cout << storage.control_block.id << endl;
    cout << sizeof(storage.data_block) << endl;
    cout << sizeof(storage.control_block) << endl;
    cout << sizeof(storage.pad) << endl;

    caos::abstract_active_object* raw = storage.control_block.get();

    return 0;
}

