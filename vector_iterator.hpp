//
// Created by Matthos Denys on 3/27/22.
//

#ifndef FT_CONTAINERS_VECTOR_ITERATOR_HPP
#define FT_CONTAINERS_VECTOR_ITERATOR_HPP


#include <clocale>
#include "utils.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
    template<typename T>
    class vector_iterator : public iterator<typename iterator_traits<T *>::iterator_category,
            typename iterator_traits<T *>::value_type,
            typename iterator_traits<T *>::difference_type,
            typename iterator_traits<T *>::pointer,
            typename iterator_traits<T *>::reference >
    {
    public:
        typedef	typename iterator<random_access_iterator_tag, T>::value_type		value_type;
        typedef	typename iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;
        typedef typename iterator<random_access_iterator_tag, T>::difference_type	difference_type;
        typedef typename iterator<random_access_iterator_tag, T>::pointer			pointer;
        typedef typename iterator<random_access_iterator_tag, T>::reference			reference;

    private:
        pointer	_p;

    public:
        vector_iterator() : _p(NULL) {};
        vector_iterator(pointer p) : _p(p) {};
        vector_iterator(const vector_iterator& it) : _p(it._p) {};
        virtual ~vector_iterator() {};

        vector_iterator&	operator=(const vector_iterator& it)
        {
            if (*this != it)
                this->_p = it._p;
            return *this;
        }

        pointer				base() const {return _p;};
        reference			operator*() const {return *_p;};
        pointer				operator->() const {return _p;};
        vector_iterator&	operator++()
        {
            ++_p;
            return *this;
        }
        vector_iterator	operator++(int)
        {
            vector_iterator<value_type> tmp(*this); ++(*this); return tmp;
        }
        vector_iterator&	operator--()
        {
            --_p;
            return *this;
        }
        vector_iterator	operator--(int)
        {
            vector_iterator<value_type>	tmp(*this);
            --_p;
            return tmp;
        }
        vector_iterator		operator+(difference_type bias) {return _p + bias;}
        vector_iterator		operator-(difference_type bias) {return _p - bias;}
        vector_iterator&	operator+=(difference_type bias) {_p += bias; return *this;}
        vector_iterator&	operator-=(difference_type bias) {_p -= bias; return *this;}
        reference			operator[](difference_type bias) {return *(_p + bias);}
        bool				operator==(const vector_iterator& right) {return _p == right.base();};
        bool				operator!=(const vector_iterator& right) {return _p != right.base();};

        operator vector_iterator<const value_type> () const
        { return (vector_iterator<const value_type>(this->_p)); }
    };

    template <typename T>
    typename ft::vector_iterator<T>::difference_type			operator==(const ft::vector_iterator<T> left, const ft::vector_iterator<T> right)
    {
        return left.base() == right.base();
    }

    template <typename T1, typename T2>
    typename ft::vector_iterator<T1>::difference_type		operator==(const ft::vector_iterator<T1> left, const ft::vector_iterator<T2> right)
    {
        return left.base() == right.base();
    }

    template <typename T>
    typename ft::vector_iterator<T>::difference_type			operator!=(const ft::vector_iterator<T> left, const ft::vector_iterator<T> right)
    {
        return left.base() != right.base();
    }

    template <typename T1, typename T2>
    typename ft::vector_iterator<T1>::difference_type		operator!=(const ft::vector_iterator<T1> left, const ft::vector_iterator<T2> right)
    {
        return left.base() != right.base();
    }

    template <typename T>
    typename ft::vector_iterator<T>::difference_type			operator>(const ft::vector_iterator<T> left, const ft::vector_iterator<T> right)
    {
        return left.base() > right.base();
    }

    template <typename T1, typename T2>
    typename ft::vector_iterator<T1>::difference_type		operator>(const ft::vector_iterator<T1> left, const ft::vector_iterator<T2> right)
    {
        return left.base() > right.base();
    }

    template <typename T>
    typename ft::vector_iterator<T>::difference_type			operator<(const ft::vector_iterator<T> left, const ft::vector_iterator<T> right)
    {
        return left.base() < right.base();
    }

    template <typename T1, typename T2>
    typename ft::vector_iterator<T1>::difference_type		operator<(const ft::vector_iterator<T1> left, const ft::vector_iterator<T2> right)
    {
        return left.base() < right.base();
    }

    template <typename T>
    typename ft::vector_iterator<T>::difference_type			operator<=(const ft::vector_iterator<T> left, const ft::vector_iterator<T> right)
    {
        return left.base() <= right.base();
    }

    template <typename T1, typename T2>
    typename ft::vector_iterator<T1>::difference_type		operator<=(const ft::vector_iterator<T1> left, const ft::vector_iterator<T2> right)
    {
        return left.base() <= right.base();
    }

    template <typename T>
    typename ft::vector_iterator<T>::difference_type			operator>=(const ft::vector_iterator<T> left, const ft::vector_iterator<T> right)
    {
        return left.base() >= right.base();
    }

    template <typename T1, typename T2>
    typename ft::vector_iterator<T1>::difference_type		operator>=(const ft::vector_iterator<T1> left, const ft::vector_iterator<T2> right)
    {
        return left.base() >= right.base();
    }

    template <typename T>
    typename ft::vector_iterator<T>							operator+(typename ft::vector_iterator<T>::difference_type n, typename ft::vector_iterator<T>& it)
    {
        return it.operator+(n);
    }

    template <typename T>
    typename ft::vector_iterator<T>::difference_type			operator-(const ft::vector_iterator<T> left, const ft::vector_iterator<T> right)
    {
        return left.base() - right.base();
    }

    template<typename T_L, typename T_R>
    typename ft::vector_iterator<T_L>::difference_type		operator-(const ft::vector_iterator<T_L> left, const ft::vector_iterator<T_R> right)
    {
        return (left.base() - right.base());
    }
};

#endif
