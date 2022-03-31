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
        /// value_type - констурктор нашего передаваемого типа например если
        /// мы передадим конструктор стриги со значением "да" то вызовится требуемый консттруктор с значением "да"
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
        pointer			_data; /// указатель на память с данными на нашу коллекцию
        size_t			_size; /// количество элементов
        size_t			_capacity; /// обьем
        allocator_type	_alloc; /// вызванный аллокатор
        pointer			_begin; /// начало наших данных
        pointer			_end; /// конец наших данных
        pointer			_capacity_end; /// TODO ???


        ///чтобы не забыть реализацию пиши себе комменты
        /// даже когда думаешь что будешь писать контейнеры каждый день



        void			reallocate(size_t n = 0)
        {

            size_t		count_to_allocate; ///будущий обьем
            pointer		tmp; ///временная дата

            /// проверяем текущий обьем
            if (_capacity == 0)
                ///если обьем был нулевой задаем единицу
                count_to_allocate = 1;

            /// если нам пришел какой либо аргумент то выставляем будущий обьем по аргументу
            else if (n)
                count_to_allocate = n;
            ///иначе текущий обьем умножим на 2
            else
                count_to_allocate = _capacity * 2;
            tmp = _data;
            ///муваем указатель даты на временный темп
            if (!(_data = _alloc.allocate(count_to_allocate)))
                ///кидаем эксепшн если не удалось реалочить
                throw std::bad_alloc();
            for (size_t i = 0; i < _size; ++i)
            {
                //выделяет новую память и копирует старую
                _alloc.construct(&_data[i], tmp[i]);
                //убивает старую память
                _alloc.destroy(&tmp[i]);
            }
            _alloc.deallocate(tmp, _capacity);
            _capacity = count_to_allocate;
        }


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
            if (!(_data = _alloc.allocate(n)))
                throw std::bad_alloc();
            for (unsigned int i = 0; i < n; ++i)
            {
                _alloc.construct(&_data[i], val);
            }
            _end = _begin + _size;
        }


        /* example    ft::vector<std::string> third (second.begin(), second.end());
         * это мы инициализируем значениями из другого контейнера с начала по конец
         *
         * */
        template <class InputIterator>
        vector (InputIterator first, InputIterator last,
                const allocator_type& alloc = allocator_type()) : _data(NULL) , _size(0),  _capacity(0), _alloc(alloc), _begin(0), _end(0) {

        }


        /* example     ft::vector<std::string> fourth (third);
        * это мы инициализируем значениями из другого контейнера копируя контейнер
        *
        * */
        vector (const vector& x) : _data(NULL), _size(0), _capacity(0), _alloc(allocator_type()), _begin(0), _end(0) {
            insert(begin(), x.begin(), x.end());
        }


        virtual ~vector() {}



        iterator				begin() {return this->_begin;};
        iterator				end() {return this->_end;};

        void                    insert(iterator position, size_type n, const value_type& val)
        {

        }

    };



}

#endif