
#include <map>
#include <string>
#include <iostream>
#include <functional>

#include "caos/active_object.hpp"
#include "caos/intrusive_ptr.hpp"
#include "caos/active_object_storage.hpp"

using namespace std;

//--------------------------------------------------------------------------------------------------

class dictionary : public caos::active_object
{
    std::map<std::string, int> dict_;

public:
    void get(std::string key, std::function<void(string,int)>&& callback)
    {
        post(&dictionary::__get, this, key, callback);
    }

private:
    void __get(const string& key, std::function<void(string,int)>&& hnd)
    {
        hnd(key, dict_[key]);
    }
};

//--------------------------------------------------------------------------------------------------

int main(int argc, char ** argv)
{
    caos::active_object_system home_system;
    caos::active_object_storage<dictionary> storage(0, &home_system);

    cout << storage.control_block.id() << endl;

    return 0;
}

