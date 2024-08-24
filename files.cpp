#include <iostream>
#include <fstream>
#include <vector>

std::vector<double> write()
{
    std::vector<double> a;

    for (double i=0; i<=10; i++)
    {
        a.push_back(i);
    }

    return a;
};


int main()
{
    std::ofstream out;          // поток для записи
    out.open("test.txt");      // открываем файл для записи
    if (out.is_open())
    {
        std::vector<double>a = write();

        for (int i = 0; i<a.size(); i++)
        {
            out << a[i] << " ";
        }
    }
    out.close(); 
    std::cout << "File has been written" << std::endl;
}