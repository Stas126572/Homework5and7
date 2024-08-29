#include <iostream>
#include "NodesList.hpp"
#include "Vector.hpp"

template<typename Conteiner>
void ConteinerTest(Conteiner nd)
{
    std::cout << std::endl;
    std::cout << "Size: " << nd.get_size() << std::endl;
    nd.push_back(3);
    std::cout << "Size: " << nd.get_size() << std::endl;
    std::cout << "Element 2: " << nd.GetElementOfIndex(0) << std::endl;
    nd.push_back(3);
    std::cout << "Size: " << nd.get_size() << std::endl;
    std::cout << "Element 2: " << nd.GetElementOfIndex(0) << std::endl;
    std::cout << "Element: " << nd.pop_back() << std::endl;
    std::cout << "Size: " << nd.get_size() << std::endl;
    std::cout << std::endl;
}

int main()
{
    Vector v;
    v.push_back(1);
    std::cout << v[0];
}