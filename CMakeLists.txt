cmake_minimum_required(VERSION 3.20)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(ft_containers main.cpp containers/Vector.hpp containers/utils/utils.hpp containers/utils/random_access_iterator.hpp)
