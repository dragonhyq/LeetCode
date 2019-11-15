#include <iostream>
int main() {
    int a = INT_MAX;
    int b = 1;
    int c = INT_MAX;
    std::cout << (a > b) << std::endl;
    std::cout << (a == b) << std::endl;
    std::cout << (c == b) << std::endl;
    std::cout << (a == c) << std::endl;
    return 0;
       
}