//
// Created by Matthos Denys on 3/27/22.
//

#ifndef REV_ITER
# define REV_ITER

# include <iostream>
# include "utils.hpp"

namespace ft
{

    class input_iterator_tag {};
    class output_iterator_tag {};
    class forward_iterator_tag : input_iterator_tag {};
    class bidirectional_iterator_tag : forward_iterator_tag {};
    class random_access_iterator_tag : bidirectional_iterator_tag {};

    template<class Iterator>
    struct iterator_traits
    {
    public:
        typedef typename	Iterator::difference_type			difference_type;
        typedef typename	Iterator::value_type				value_type;
        typedef typename	Iterator::pointer					pointer;
        typedef typename	Iterator::reference					reference;
        typedef typename	Iterator::iterator_category			iterator_category;
    };

    template<class T>
    struct iterator_traits<T *>
    {
    public:
        typedef std::ptrdiff_t						difference_type;
        typedef T									value_type;
        typedef T*									pointer;
        typedef T&									reference;
        typedef ft::random_access_iterator_tag		iterator_category;
    };

    template<class T>
    struct iterator_traits<const T *>
    {
    public:
        typedef std::ptrdiff_t						difference_type;
        typedef T									value_type;
        typedef const T*							pointer;
        typedef const T&							reference;
        typedef ft::random_access_iterator_tag		iterator_category;
    };

    template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef T			value_type;
        typedef Distance	difference_type;
        typedef Pointer		pointer;
        typedef Reference	reference;
        typedef Category	iterator_category;
    };


    template<typename Iter>
    class reverse_iterator : public iterator<typename iterator_traits<Iter>::iterator_category,
            typename iterator_traits<Iter>::value_type,
            typename iterator_traits<Iter>::difference_type,
            typename iterator_traits<Iter>::pointer,
            typename iterator_traits<Iter>::reference >
    {
    public:
        typedef	Iter																		iterator_type;
        typedef typename ft::iterator_traits<iterator_type>::iterator_category 				iterator_category;
        typedef typename ft::iterator_traits<iterator_type>::value_type        				value_type;
        typedef typename ft::iterator_traits<iterator_type>::difference_type   				difference_type;
        typedef typename ft::iterator_traits<iterator_type>::pointer           				pointer;
        typedef typename ft::iterator_traits<iterator_type>::reference         				reference;

    private:
        iterator_type	_p;

    public:
        reverse_iterator() : _p(NULL) {};
        reverse_iterator(iterator_type it) : _p(it) {};
        ~reverse_iterator() {};
        template <class T>
        reverse_iterator(const reverse_iterator<T>& it) : _p(it.base()) {};

        reverse_iterator&	operator=(const reverse_iterator& it)
        {
            if (this != it)
                this->_p = it._p;
            return *this;
        }

        iterator_type		base() const {return _p;};
        // pointer				base() const {return _p.base();};
        reference			operator*() const {return *_p;};
        pointer				operator->() const {return _p.operator->();};
        reverse_iterator&	operator++()
        {
            --_p;
            return *this;
        }
        reverse_iterator	operator++(int)
        {
            reverse_iterator<iterator_type> tmp(*this); --(*this); return tmp;
        }
        reverse_iterator&	operator--()
        {
            ++_p;
            return *this;
        }
        reverse_iterator	operator--(int)
        {
            reverse_iterator<value_type>	tmp(*this);
            ++_p;
            return tmp;
        }
        reverse_iterator		operator+(difference_type bias) {return _p - bias;}
        reverse_iterator		operator-(difference_type bias) {return _p + bias;}
        reverse_iterator&		operator+=(difference_type bias) {_p -= bias; return *this;}
        reverse_iterator&		operator-=(difference_type bias) {_p += bias; return *this;}
        reference				operator[](difference_type bias) {return *(_p - bias);}
        bool					operator==(const reverse_iterator& right) {return _p == right.base();};
        bool					operator!=(const reverse_iterator& right) {return _p != right.base();};

    };

    template <typename T>
    typename ft::reverse_iterator<T>::difference_type			operator==(const ft::reverse_iterator<T> left, const ft::reverse_iterator<T> right)
    {
        return left.base() == right.base();
    }

    template <typename T1, typename T2>
    typename ft::reverse_iterator<T1>::difference_type		operator==(const ft::reverse_iterator<T1> left, const ft::reverse_iterator<T2> right)
    {
        return left.base() == right.base();
    }

    template <typename T>
    typename ft::reverse_iterator<T>::difference_type			operator!=(const ft::reverse_iterator<T> left, const ft::reverse_iterator<T> right)
    {
        return left.base() != right.base();
    }

    template <typename T1, typename T2>
    typename ft::reverse_iterator<T1>::difference_type		operator!=(const ft::reverse_iterator<T1> left, const ft::reverse_iterator<T2> right)
    {
        return left.base() != right.base();
    }

    template <typename T>
    typename ft::reverse_iterator<T>::difference_type			operator>(const ft::reverse_iterator<T> left, const ft::reverse_iterator<T> right)
    {
        return left.base() > right.base();
    }

    template <typename T1, typename T2>
    typename ft::reverse_iterator<T1>::difference_type		operator>(const ft::reverse_iterator<T1> left, const ft::reverse_iterator<T2> right)
    {
        return left.base() > right.base();
    }

    template <typename T>
    typename ft::reverse_iterator<T>::difference_type			operator<(const ft::reverse_iterator<T> left, const ft::reverse_iterator<T> right)
    {
        return left.base() < right.base();
    }

    template <typename T1, typename T2>
    typename ft::reverse_iterator<T1>::difference_type		operator<(const ft::reverse_iterator<T1> left, const ft::reverse_iterator<T2> right)
    {
        return left.base() < right.base();
    }

    template <typename T>
    typename ft::reverse_iterator<T>::difference_type			operator<=(const ft::reverse_iterator<T> left, const ft::reverse_iterator<T> right)
    {
        return left.base() <= right.base();
    }

    template <typename T1, typename T2>
    typename ft::reverse_iterator<T1>::difference_type		operator<=(const ft::reverse_iterator<T1> left, const ft::reverse_iterator<T2> right)
    {
        return left.base() <= right.base();
    }

    template <typename T>
    typename ft::reverse_iterator<T>::difference_type			operator>=(const ft::reverse_iterator<T> left, const ft::reverse_iterator<T> right)
    {
        return left.base() >= right.base();
    }

    template <typename T1, typename T2>
    typename ft::reverse_iterator<T1>::difference_type		operator>=(const ft::reverse_iterator<T1> left, const ft::reverse_iterator<T2> right)
    {
        return left.base() >= right.base();
    }

    template <typename T>
    typename ft::reverse_iterator<T>							operator+(typename ft::reverse_iterator<T>::difference_type n, typename ft::reverse_iterator<T>& it)
    {
        return it.operator+(n);
    }

    template <typename T>
    typename ft::reverse_iterator<T>::difference_type			operator-(const ft::reverse_iterator<T> left, const ft::reverse_iterator<T> right)
    {
        return left.base() + right.base();
    }

    template <typename T_L, typename T_R>
    typename ft::reverse_iterator<T_L>::difference_type			operator-(const ft::reverse_iterator<T_L> left, const ft::reverse_iterator<T_R> right)
    {
        return (left.base() + right.base());
    }

}

#endif