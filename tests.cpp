#include <iostream>
#include <algorithm>
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "set.hpp"


# ifdef STD
#  define ft std
#endif

void	print_string(std::string x)
{
    std::cout << x << std::endl;
}

void	print(int x)
{
    std::cout << x << ' ';
}

template<class container_type>
void	print_container_info(const container_type& c)
{
    std::cout << "empty = " << c.empty() << std::endl;
    std::cout << "size = " << c.size() << std::endl;
    // std::cout << "capacity = " << c.capacity() << std::endl << std::endl;
    std::cout << "max_size = " << c.max_size() << std::endl << std::endl;
}

int	main()
{
    std::cout << "******************VECTOR********************\n" << std::endl;

    ft::vector<std::string>  v;
    print_container_info(v);
    v.push_back("Hello");
    v.push_back("World");
    v.push_back("");
    v.push_back(".................................................................................");
    v.push_back("my name is msamual");
    std::for_each(v.begin(), v.end(), print_string);
    print_container_info(v);
    v.resize(10);
    v.reserve(200);
    print_container_info(v);
    print_string(v[0]);
    print_string(v[3]);
    print_string(v.front());
    print_string(v.back());
    v.assign(20, "hello world");
    std::for_each(v.begin(), v.end(), print_string);
    print_container_info(v);
    while (v.size() != 0)
        v.pop_back();
    std::for_each(v.begin(), v.end(), print_string);
    print_container_info(v);
    v.insert(v.begin(), "hello world!");
    std::for_each(v.begin(), v.end(), print_string);
    print_container_info(v);

    ft::vector<int>		i;
    print_container_info(i);
    i.push_back(1024);
    i.push_back(2048);
    i.push_back(4096);
    i.push_back(8192);
    i.push_back(2147483647);
    std::for_each(i.begin(), i.end(), print);
    print_container_info(i);
    i.resize(10);
    i.reserve(200);
    print_container_info(i);
    print(i[1]);
    print(i.at(3));
    i.assign(10, 5);
    i.assign(i.begin(), i.begin() + 2);
    std::for_each(i.begin(), i.end(), print);
    print_container_info(i);
    i.erase(i.end() - 3);
    ft::vector<int>		j;
    j.push_back(1);
    j.push_back(2);
    j.push_back(3);
    j.erase(j.begin()+1, j.end()-2);
    j.swap(i);
    std::for_each(i.begin(), i.end(), print);
    print_container_info(i);
    std::for_each(j.begin(), j.end(), print);
    print_container_info(j);

    try{print(i.at(100));}catch(const std::exception& e){std::cerr << e.what() << '\n';}




    std::cout << "******************STACK********************\n" << std::endl;

    ft::stack<double>	s;
    ft::stack<double>	s1;
    std::cout << "empty = " << s.empty() << std::endl;
    std::cout << "size = " << s.size() << std::endl;
    s.push(2.5);
    s.push(3.5);
    s.push(4.5);
    s.push(5.0);
    while (s.size())
    {
        std::cout << s.top() << std::endl;
        s.pop();
    }
    std::cout << "s == s1: " << (s == s1) << std::endl;
    s.push(2.5);
    s.push(3.5);
    s.push(4.5);
    s.push(5.0);
    s1.push(2.5);
    s1.push(3.5);
    s1.push(4.5);
    s1.push(5.0);
    std::cout << "s == s1: " << (s == s1) << std::endl;
    s1.pop();
    std::cout << "s == s1: " << (s != s1) << std::endl;



    std::cout << "******************MAP********************\n" << std::endl;


    ft::map<std::string, int>	m;
    print_container_info(m);
    m.insert(ft::make_pair("Hello", 1));
    m.insert(ft::make_pair("Hello", 2));
    m.insert(ft::make_pair("world", 2));
    m.insert(ft::make_pair("it's a", 3));
    m.insert(ft::make_pair("MAP", 4));
    for (ft::map<std::string, int>::iterator it = m.begin(); it != m.end(); ++it)
        std::cout << it->first << " : " << it->second << std::endl;
    ft::map<std::string, int>	m1(m);
    for (ft::map<std::string, int>::iterator it = m1.begin(); it != m1.end(); ++it)
        std::cout << it->first << " : " << it->second << std::endl;
    ft::map<std::string, int>	m2;
    m2 = m1;
    for (ft::map<std::string, int>::iterator it = m2.begin(); it != m2.end(); ++it)
        std::cout << it->first << " : " << it->second << std::endl;
    ft::map<std::string, int>	m3;
    m3.insert(m2.begin(), m2.end());
    m1.erase(m1.begin());
    std::cout << m2.count("MAP") << std::endl;
    if (m2.find("MAP") != m2.end())
        m2.erase("MAP");
    std::cout << m2.count("MAP") << std::endl;
    m3.erase(m3.begin(), m3.find("its' a"));
    m1.swap(m3);
    m.clear();
    for (ft::map<std::string, int>::iterator it = m.begin(); it != m.end(); ++it)
        std::cout << it->first << " : " << it->second << std::endl;
    for (ft::map<std::string, int>::iterator it = m1.begin(); it != m1.end(); ++it)
        std::cout << it->first << " : " << it->second << std::endl;
    for (ft::map<std::string, int>::iterator it = m2.begin(); it != m2.end(); ++it)
        std::cout << it->first << " : " << it->second << std::endl;
    for (ft::map<std::string, int>::iterator it = m3.begin(); it != m3.end(); ++it)
        std::cout << it->first << " : " << it->second << std::endl;


    std::cout << "******************SET********************\n" << std::endl;


    ft::set<std::string>	Set;
    print_container_info(Set);
    Set.insert("Hello");
    Set.insert("Hello");
    Set.insert("world");
    Set.insert("it's a");
    Set.insert("set");
    for (ft::set<std::string>::iterator it = Set.begin(); it != Set.end(); ++it)
        std::cout << *it << std::endl;
    ft::set<std::string>	Set1(Set);
    for (ft::set<std::string>::iterator it = Set1.begin(); it != Set1.end(); ++it)
        std::cout << *it << std::endl;
    ft::set<std::string>	Set2;
    Set2 = Set1;
    for (ft::set<std::string>::iterator it = Set2.begin(); it != Set2.end(); ++it)
        std::cout << *it << std::endl;
    ft::set<std::string>	Set3;
    Set3.insert(Set2.begin(), Set2.end());
    Set1.erase(Set1.begin());
    std::cout << Set2.count("set") << std::endl;
    if (Set2.find("set") != Set2.end())
        Set2.erase("set");
    std::cout << Set2.count("set") << std::endl;
    Set3.erase(Set3.begin(), Set3.find("its' a"));
    Set1.swap(Set3);
    Set.clear();
    for (ft::set<std::string>::iterator it = Set.begin(); it != Set.end(); ++it)
        std::cout << *it << std::endl;
    for (ft::set<std::string>::iterator it = Set1.begin(); it != Set1.end(); ++it)
        std::cout << *it << std::endl;
    for (ft::set<std::string>::iterator it = Set2.begin(); it != Set2.end(); ++it)
        std::cout << *it << std::endl;
    for (ft::set<std::string>::iterator it = Set3.begin(); it != Set3.end(); ++it)
        std::cout << *it << std::endl;

    // while(1) ;
    return 0;
}