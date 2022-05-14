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

    first["dadadad"]=232323;
//    first["tes"]=23;
//    first["dadd"]=233;

//    std::cout << (first.find("da"))->second << std::endl;
//
//std::cout << "teest" << std::endl;

    return 0;
}


