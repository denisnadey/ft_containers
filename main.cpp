#include <iostream>
#include <vector>

#include "containers/Vector.hpp"

using namespace ft;
using namespace std;




class Cat {
private:
    string test;
public:
    Cat(string test){
        this->test = test;
    }

    string getCat() { return this->test;};
} meow = Cat("da");






int main() {
    std::vector<string> test;
        test.push_back("test");

    std::cout << meow.getCat() << std::endl;

    return 0;
}


/*
 *
 * Task one
 * почитать все коменты [X]
 *
 * Task two
 * explicit почитать []
 *
 *
 */