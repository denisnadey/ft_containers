#include <iostream>
#include <vector>

#include "Vector.hpp"

using namespace ft;











int main() {

    ft::vector<std::string> first;
    ft::vector<std::string> second (5,"da");

    ft::vector<std::string> third (second.begin(), second.end());
    ft::vector<std::string> fourth (third);

    return 0;
}


