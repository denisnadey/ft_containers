#include <iostream>
#include <vector>
#include <map>

#include "vector.hpp"
#include "map.hpp"

using namespace ft;





/*
 * Разобраться как работать с мапой в плюсах
 * сравнить псевдокод и фукнции сереги
 * узнать что такое поворот
 * и все методы описанные в контейнере
 * посмотреть визуализации
 */





int main() {



    ft::map<std::string, int> first;

    first["da"]=80;


    std::cout << (first.find("da"))->second << std::endl;

std::cout << "teest" << std::endl;

    return 0;
}


