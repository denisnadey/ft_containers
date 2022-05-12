#include <iostream>
#include <vector>
#include <map>

#include "vector.hpp"
#include "map.hpp"

using namespace ft;





/*
 * пофиксить сегу в деструкторе мапы
 */





int main() {



    ft::map<std::string, int> first;

    first["da"]=80;


    std::cout << (first.find("da"))->second << std::endl;

std::cout << "teest" << std::endl;

    return 0;
}


