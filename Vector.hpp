//
// Created by Matthos Denys on 1/16/22.
//
#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "vector_iterator.hpp"
# include <memory>
# include <algorithm>
# include <cstddef>
# include <tgmath.h>


//Открыть твои контейнерв
//        Открыть сайт спп ком
//        Разобраться какие методы есть у вектора и поля
//        Разобраться с каждым методом
//        Разобраться что такое итераторы
//        Посмотреть серегины итераторы
//Реализация
//        Написать класс вектор
//Описать все тайпдефы
//        Определится с итераторы и их написать
//        Реализовать все методы по очереди
//
//
//
//Порядок реализации
//Вектор
//        Стек
//Мапа
//        Сет

namespace ft {



    template<typename  T, typename  Alloc = std::allocator<T> >
    class vector {
    public:
        typedef 			T												value_type;
        typedef				Alloc											allocator_type;
        typedef typename	allocator_type::reference						reference;
        typedef typename	allocator_type::const_reference					const_reference;
        typedef typename	allocator_type::pointer							pointer;
        typedef typename	allocator_type::const_pointer					const_pointer;
        typedef typename	ft::vector_iterator<value_type>					iterator;
        typedef typename	ft::vector_iterator<const value_type>			const_iterator;
        typedef typename	ft::reverse_iterator<iterator>					reverse_iterator;
        typedef typename	ft::reverse_iterator<const_iterator>			const_reverse_iterator;
        typedef typename	ft::iterator_traits<iterator>::difference_type	difference_type;
        typedef 			size_t											size_type;




    private:
        pointer			_data;
        size_t			_size;
        size_t			_capacity;
        allocator_type	_alloc;
        pointer			_begin;
        pointer			_end;
        pointer			_capacity_end;





        /* constructors vector */
    public:






        /* example   ft::vector<std::string> tmp;
         * это требуется инициализации пустой коллекции
         * */
        explicit  vector(const allocator_type &alloc = allocator_type()) : _data(NULL) , _size(0), _capacity(0), _alloc(alloc), _begin(0), _end(0) {

        }

        /* example   ft::vector<std::string> second (5,"da");;
            * это мы инициализируем 5 элементов со значением "da"
            * */
        explicit vector(size_type n, const value_type& val = value_type(),
                         const allocator_type& alloc = allocator_type()) : _data(NULL),  _size(n),  _capacity(n), _alloc(alloc)   {

        }


        /* example    ft::vector<std::string> third (second.begin(), second.end());
         * это мы инициализируем значениями из другого контейнера с начала по конец
         *
         * */
        template <class InputIterator>
        vector (InputIterator first, InputIterator last,
                const allocator_type& alloc = allocator_type()) :_data(NULL) , _size(0),  _capacity(0), _alloc(alloc), _begin(0), _end(0) {

        }


        /* example     ft::vector<std::string> fourth (third);
        * это мы инициализируем значениями из другого контейнера копируя контейнер
        *
        * */
        vector (const vector& x) : _data(NULL), _size(0), _capacity(0), _alloc(allocator_type()), _begin(0), _end(0) {

        }


        virtual ~vector() {}

        iterator				begin() {return this->_begin;};
        iterator				end() {return this->_end;};
    };



}

#endif