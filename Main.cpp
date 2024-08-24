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
    std::cout << "Element 2: " << nd.GIE(0) << std::endl;
    nd.push_back(3);
    std::cout << "Size: " << nd.get_size() << std::endl;
    std::cout << "Element 2: " << nd.GIE(0) << std::endl;
    std::cout << "Element: " << nd.pop_back() << std::endl;
    std::cout << "Size: " << nd.get_size() << std::endl;
    std::cout << std::endl;
}

int main()
{
    NodesList<int> nd;
    Vector<int> vc;
    ConteinerTest(vc);
}