#include <iostream>
#include <string>
#include <string.h>

class db
{
public:
    template<typename T>
        struct Input { typedef T type; };

    template<typename T>
        void setValue(typename Input<T>::type newValue)
    {
        setValue(Input<T>(), newValue);
    }
private:
    void* data;
    void setValue(Input<std::string>, typename Input<std::string>::type newValue)
    {
        data = (void*) new char[newValue.size()+1];
        strcpy((char*)data, newValue.c_str());
        std::cout << "string: \"" << (char*)data << "\"\n";
    }
};

int main()
{
    db dbObj;
    std::string str = "Hello world";
    dbObj.setValue<std::string>(str);
    std::cout << "This is the end!\n";
    return 0;
}
