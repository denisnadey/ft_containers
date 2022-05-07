#ifndef MAP_ITERATOR
# define MAP_ITERATOR

# include "btree.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
    template<class T, class Node>
    class map_iterator : public ft::iterator<typename ft::iterator_traits<T *>::iterator_category,
            typename ft::iterator_traits<T *>::value_type,
            typename ft::iterator_traits<T *>::difference_type,
            typename ft::iterator_traits<T *>::pointer,
            typename ft::iterator_traits<T *>::reference >
    {
    public:
        typedef	typename ft::iterator<bidirectional_iterator_tag, T>::value_type		value_type;
        typedef	typename ft::iterator<bidirectional_iterator_tag, T>::iterator_category	iterator_category;
        typedef typename ft::iterator<bidirectional_iterator_tag, T>::difference_type	difference_type;
        typedef typename ft::iterator<bidirectional_iterator_tag, T>::pointer			pointer;
        typedef typename ft::iterator<bidirectional_iterator_tag, T>::reference			reference;
        typedef			 Node*															node_pointer;

    private:
        node_pointer	_p;

        void	previos()
        {
            if (_p->_left->_flag != 2)
            {
                _p = _p->_left;
                while (_p->_flag != 1 && _p->_right->_flag == 0)
                    _p = _p->_right;
            }
            else if (_p == _p->_parent->_left)
            {
                while(_p == _p->_parent->_left)
                    _p = _p->_parent;
                _p = _p->_parent;
            }
            else
                _p = _p->_parent;
        }

        void	next()
        {
            if (_p->_right->_flag != 2)
            {
                _p = _p->_right;
                while (_p->_flag != 1 && _p->_left->_flag != 2)
                    _p = _p->_left;
            }
            else
            {
                node_pointer	tmp;
                tmp = _p;
                _p = _p->_parent;
                while(_p->_left != tmp)
                {
                    tmp = _p;
                    _p = _p->_parent;
                }
            }
        }

    public:
        map_iterator() : _p(nullptr) {};
        map_iterator(node_pointer p) : _p(p) {};
        map_iterator(const map_iterator& it) : _p(it._p) {};
        virtual ~map_iterator() {};

        map_iterator&		operator=(const map_iterator& it) {_p = it._p; return *this;}

        node_pointer		base() const {return _p;};
        reference			operator*()	{return _p->_data;};
        const reference		operator*() const {return _p->_data;};
        pointer				operator->() {return &_p->_data;};
        const pointer		operator->() const {return &_p->_data;};
        map_iterator&		operator++() {next(); return *this;};
        map_iterator		operator++(int)
        {
            map_iterator	tmp(*this);
            next();
            return tmp;
        };
        map_iterator&		operator--() {previos(); return *this;};
        map_iterator		operator--(int)
        {
            map_iterator	tmp(*this);
            previos();
            return tmp;
        }
        map_iterator&		operator+=(int value)
        {
            if (value > 0)
            {
                for (int i = 0; i < value; ++i)
                    next();
            }
            else
            {
                for (int i = 0; i > value; --i)
                    previos();
            }
            return *this;
        }
        map_iterator&		operator-=(int value) {return operator+=(-value);}
        map_iterator		operator+(int value) const
        {
            map_iterator	tmp(*this);
            return tmp += value;
        }
        map_iterator		operator-(int value)
        {
            map_iterator	tmp(*this);
            return tmp -= value;
        }
        bool				operator==(map_iterator const &other) const
        {
            return (this->_p == other._p);
        }
        bool				operator!=(map_iterator const &other) const
        {
            return (this->_p != other._p);
        }
        bool				operator<(map_iterator const &other) const
        {
            return (this->_p < other._p);
        }
        bool				operator<=(map_iterator const &other) const
        {
            return (this->_p <= other._p);
        }
        bool				operator>(map_iterator const &other) const
        {
            return (this->_p > other._p);
        }
        bool				operator>=(map_iterator const &other) const
        {
            return (this->_p >= other._p);
        }

        operator map_iterator<const value_type, const Node> () const
        { return map_iterator<const value_type, const Node>(_p);}
    };

};

#endif