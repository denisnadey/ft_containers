#include <iostream>
#include <vector>

#include "vector.hpp"

using namespace ft;





///TODO insert,





int main() {

    ft::vector<std::string> test ;
    test.push_back("da");
    ft::vector<std::string>::iterator iterator = test.end();
    test.insert(iterator, "kek");

    for (ft::vector<std::string>::iterator it = test.begin();  it != test.end(); it++ )
    {
        std::cout << *it << std::endl;
    }

    return 0;
}


