#include <iostream>

int main() {
    int p[3] = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        std::cout << "Address of p[" << i << "] = " << &p[i] << std::endl;
    }
    std::cout << "Address of (p[0] + 1) = " << (&p[0] + 1) << std::endl;
    std::cout << "Value of (p[0] + 1) = " << *(&p[0] + 1) << std::endl;
    return 0;
}