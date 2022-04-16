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
        size_t			_capacity; /// обьем памяти выделленный для контейнера ( там может быть больше чем нужно)
        allocator_type	_alloc; /// вызванный аллокатор
        pointer			_begin; /// начало наших данных на первый  элемент
        pointer			_end; ///   конец наших данных указатель на последний элемент


        ///чтобы не забыть реализацию пиши себе комменты
        /// даже когда думаешь что будешь писать контейнеры каждый день


        void			reallocate(size_t n = 0)
        {

            size_t		count_to_allocate; ///будущий обьемa
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
            insert(begin(), first, last);
        }


        /* example     ft::vector<std::string> fourth (third);
        * это мы инициализируем значениями из другого контейнера копируя контейнер
        *
        * */
        vector (const vector& x) : _data(NULL), _size(0), _capacity(0), _alloc(allocator_type()), _begin(0), _end(0) {
            //TODO refactor this
            insert(begin(), x.begin(), x.end());
        }


        virtual ~vector() {}

        void	clear()
        {
            while (_size)
                pop_back();
        }

        iterator		erase(iterator position)
        {
            iterator	res = position;
            iterator	it = _begin;
            while (it != _end && it != position)
                ++it;
            _alloc.destroy(&*it);
            while (it != end())
                *it = *(it++);
            --_size;
            --_end;
            return res;
        }

        iterator		erase(iterator first, iterator last)
        {
            iterator	res = first;
            size_type	n = ft::distance(first, last);

            for (iterator it = first; it != last; ++it)
                _alloc.destroy(&*it);
            for (iterator it = last; it != end(); ++it)
                _alloc.construct(&*first++, *it);
            _size -= n;
            _end = _begin + _size;
            return res;
        }

        allocator_type	get_allocator() const
        {
            return _alloc;
        }


        void			swap(vector<T>& x)
        {
            ft::swap(&_data, &x._data);
            ft::swap(&_size, &x._size);
            ft::swap(&_begin, &x._begin);
            ft::swap(&_end, &x._end);
            ft::swap(&_capacity, &x._capacity);
            ft::swap(&_alloc, &x._alloc);
        }

        size_type				size() const {return _size;};
        size_type				capacity() const {return _capacity;};
        size_type				max_size() const {return _alloc.max_size();};
        bool					empty() const {return begin() == end();};
        void					reserve(size_type n)
        {
            if (n > _capacity)
            {
                reallocate(n);
                _begin = _data;
                _end = _begin + _size;
                _capacity = n;
            }
        }

        vector&			operator=(const vector& x)
        {
            clear();
            insert(x.begin(), x.end());
        }


        void					resize(size_type n, value_type value = value_type())
        {
            if (n > _capacity)
            {
                this->reallocate(n > _capacity * 2 ? n : 0);
                while (_size < n)
                    _alloc.construct(&_data[_size++], value);
            }
            else if (n > _size)
            {
                while (_size < n)
                    _alloc.construct(&_data[_size++], value);
            }
            else
            {
                while (_size > n)
                    _alloc.destroy(&_data[_size-- - 1]);
            }
            _begin = _data;
            _end = _begin + _size;

        }

        reference		operator[](size_type n) {return _data[n];};
        reference		front() {return *_data;};
        const_reference	front() const {return *_data;};
        reference		back() {return *(_end - 1);};
        const_reference	back() const {return *(_end - 1);};
        reference		at(size_type n)
        {
            if (n >= _size)
                throw std::out_of_range("ft::vector: out of range");
            else
                return *(_data + n);
        }


        iterator				begin() {return this->_begin;};
        iterator				end() {return this->_end;};
        const_iterator			begin() const {return this->_begin;};
        const_iterator			end() const {return this->_end;};
        reverse_iterator		rbegin() {return reverse_iterator(end() - 1);};
        reverse_iterator		rend() {return reverse_iterator(begin() - 1);};
        const_reverse_iterator	rbegin() const {return reverse_iterator(end() - 1);};
        const_reverse_iterator	rend() const {return reverse_iterator(begin() - 1);};

        void					assign(size_type n, const value_type& val)
        {
            if (_capacity < n)
            {
                reserve(n);
                while (_size)
                    _alloc.destroy(&_data[_size-- - 1]);
                while (_size < n)
                    _alloc.construct(&_data[_size++], val);
            }
            else if (_size > n)
            {
                for (size_t i = 0; i < _size; ++i)
                {
                    _alloc.destroy(&_data[i]);
                    if (i < n)
                        _alloc.construct(&_data[i], val);
                }
            }
            else
            {
                for (size_t i = 0; i < n; ++i)
                {
                    if (i < _size)
                        _alloc.destroy(&_data[i]);
                    _alloc.construct(&_data[i], val);
                }
            }
            _size = n;
            _end = _begin + _size;
        }


        template <class InputIterator>
        void	assign(
                typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                        InputIterator>::type first, InputIterator last)
        {
            size_type	n = ft::distance(first, last);
            if (_capacity < n)
                reserve(n);
            for (size_type i = 0; first != last; ++i)
            {
                if (i < _size)
                    _alloc.destroy(&_data[i]);
                _alloc.construct(&_data[i], *first++);
            }
            for (size_type i = _size; i < n; ++i)
                _alloc.destroy(&_data[i]);
            _size = n;
            _end = _begin + _size;
        }


        void			insert(iterator position, size_type n, const value_type& value)
        {
            if (!n)
                return ;
            if (_capacity < _size + n)
            {
                size_type	count_to_allocate = _size + n > _capacity * 2 ? _size + n : _capacity * 2;
                pointer		new_data;
                iterator	it = begin();
                size_type	i;

                if (!(new_data = _alloc.allocate(count_to_allocate)))
                {
                    ///кидаем эксепшн если не удалось реалочить
                    throw std::bad_alloc();
                }

                for (i = 0; it != position; ++i)
                    _alloc.construct(new_data + i, *it++);
                for (size_type j = 0; j < n; ++j)
                    _alloc.construct(new_data + i++, value);
                for (; it != end(); ++i)
                    _alloc.construct(new_data + i, *it++);
                for (size_type j = 0; j < _size; ++j)
                    _alloc.destroy(_data + j);
                _data = new_data;
                _size += n;
                _capacity = count_to_allocate;
                _begin = _data;
                _end = _data + _size;

            }
            else
            {
                size_type	tail_size = end() - position;
                value_type	tmp[tail_size];
                iterator	tail = position;

                for (size_type i = 0; tail != end(); ++i)
                    _alloc.construct(&tmp[i], *tail++);
                for (size_type i = 0; i < n; ++i)
                {
                    _alloc.destroy(&*position);
                    _alloc.construct(&*position++, value);
                }
                for (size_type	i = 0; i < tail_size; ++i)
                {
                    _alloc.construct(&*position++, tmp[i]);
                    _alloc.destroy(tmp + i);
                }
                _size += n;
                _end += n;
            }
        }


        template <class InputIterator>
        void			insert(iterator position, InputIterator first, InputIterator last)
        {
            if (first == last)
                return;
            size_type distance = ft::distance(first, last);
            if (_capacity < _size  + distance)
            {
                size_type	count_to_allocate = _size + distance > _capacity * 2 ? _size + distance : _capacity * 2;
                pointer new_data;
                if (!(new_data = _alloc.allocate(count_to_allocate)))
                {
                    ///кидаем эксепшн если не удалось реалочить
                    throw std::bad_alloc();
                }
                iterator it = begin();
                size_type i;

                for(i = 0; i != position; ++i)
                {
                    _alloc.construct(new_data + i, *it++);
                }
                for (size_type j = 0; j < distance; ++j)
                {
                    _alloc.construct(new_data + i++, *first++ );
                }
                for (; it != end(); ++i)
                {
                    _alloc.construct(new_data + i, *it++);
                }
                for (size_type j = 0; j < _size; ++j)
                {
                    _alloc.destroy(_data + j);
                }

                _data = new_data;
                _size += distance;
                _capacity = count_to_allocate;
                _begin = _data;
                _end = _data + _size;

            }
            else {
                size_type	tail_size = end() - position;
                value_type	tmp[tail_size];
                iterator	tail = position;

                for (size_type i = 0; tail != end(); ++i)
                    _alloc.construct(&tmp[i], *tail++);
                for (size_type i = 0; first != last; ++i)
                {
                    _alloc.destroy(&*position);
                    _alloc.construct(&*position++, *first++);
                }
                for (size_type i = 0; i < tail_size; ++i)
                {
                    _alloc.construct(&*position++, tmp[i]);
                    _alloc.destroy(tmp + i);
                }
                _size += distance;
                _end += distance;
            }
        }


        iterator insert(iterator position, const value_type& value)
        {
            size_type pos = position - begin();
            insert(position, 1, value);
            return begin() + pos;
        }


        void        pop_back()
        {
            _alloc.destroy(&_data[--_size]);
            --_end;
        }

        void push_back(const value_type& value)
        {
            if (_size == _capacity)
            {
                this->reallocate();
            }
            _alloc.construct(&_data[_size++], value);
            _begin = _data;
            _end = _begin + _size;
        }




    };

    template <class T, class Alloc>
    bool				operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class T, class Alloc>
    bool				operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return lhs.size() != rhs.size() || !ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class T, class Alloc>
    bool				operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool				operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
    }

    template <class T, class Alloc>
    bool				operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
    }

    template <class T, class Alloc>
    bool				operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

}


#endif