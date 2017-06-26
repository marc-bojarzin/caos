
#include <map>
#include <string>
#include <iostream>
#include <functional>

#include "caos/local_active_object.hpp"
#include "caos/intrusive_ptr.hpp"
#include "caos/active_object_storage.hpp"

using namespace std;

//--------------------------------------------------------------------------------------------------

class Dictionary : public caos::local_active_object
{
    std::map<std::string, int> dict_;

public:
    void get(std::string key, std::function<void(string,int)>&& callback)
    {
        post(&Dictionary::__get, this, key, callback);
    }

private:
    void __get(const string& key, std::function<void(string,int)>& hnd)
    {
        hnd(key, dict_[key]);
    }
};

//--------------------------------------------------------------------------------------------------

int main(int argc, char ** argv)
{
    using active_object_hnd = caos::intrusive_ptr<caos::abstract_active_object>;

    caos::active_object_storage<Dictionary> storage(0, nullptr);

    cout << storage.control_block.id << endl;
    cout << sizeof(storage.data_block) << endl;
    cout << sizeof(storage.control_block) << endl;
    cout << sizeof(storage.pad) << endl;

    caos::abstract_active_object* raw = storage.control_block.get();

    return 0;
}

