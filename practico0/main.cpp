#include <iostream>
#include <vector.h>

int main()
{
    Vector v1(1, 2, 3);
    std::cout << v1 << std::endl;
    Vector v2(4, 5, 6);
    std::cout << v2 << std::endl;
    Vector v3 = v2 - v1;

    std::cout << v3 << std::endl;
    return 0;
}
