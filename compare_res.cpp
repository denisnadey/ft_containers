#include <iostream>
#include <fstream>
#include <sstream>

#define GREEN "\x1B[32m"
#define RED "\x1B[31m"

int main()
{
    std::ifstream	my("my.txt");
    std::ifstream	orig("orig.txt");

    std::string	strmy;
    std::string	strorig;
    std::ostringstream os1;
    std::ostringstream os2;
    my >> os1.rdbuf();
    orig >> os2.rdbuf();
    strmy = os1.str();
    strorig = os2.str();


    if (strmy == strorig)
        std::cout << GREEN << "OK" << std::endl;
    else
        std::cout << RED << "FAIL" << std::endl;
}