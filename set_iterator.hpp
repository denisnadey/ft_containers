#ifndef SET_ITERATOR
# define SET_ITERATOR

# include "btree.hpp"
# include "reverse_iterator.hpp"


namespace ft
{
    template<class T, class Node>
    class set_iterator : public ft::iterator<typename ft::iterator_traits<T *>::iterator_category,
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
        set_iterator() : _p(nullptr) {};
        set_iterator(node_pointer p) : _p(p) {};
        set_iterator(const set_iterator& it) : _p(it._p) {};
        virtual ~set_iterator() {};

        set_iterator&		operator=(const set_iterator& it) {_p = it._p; return *this;}

        node_pointer		base() const {return _p;};
        reference			operator*()	{return _p->_data;};
        const reference		operator*() const {return _p->_data;};
        pointer				operator->() {return &_p->_data;};
        const pointer		operator->() const {return &_p->_data;};
        set_iterator&		operator++() {next(); return *this;};
        set_iterator		operator++(int)
        {
            set_iterator	tmp(*this);
            next();
            return tmp;
        };
        set_iterator&		operator--() {previos(); return *this;};
        set_iterator		operator--(int)
        {
            set_iterator	tmp(*this);
            previos();
            return tmp;
        }
        set_iterator&		operator+=(int value)
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
        set_iterator&		operator-=(int value) {return operator+=(-value);}
        set_iterator		operator+(int value) const
        {
            set_iterator	tmp(*this);
            return tmp += value;
        }
        set_iterator		operator-(int value)
        {
            set_iterator	tmp(*this);
            return tmp -= value;
        }
        bool				operator==(set_iterator const &other) const
        {
            return (this->_p == other._p);
        }
        bool				operator!=(set_iterator const &other) const
        {
            return (this->_p != other._p);
        }
        bool				operator<(set_iterator const &other) const
        {
            return (this->_p < other._p);
        }
        bool				operator<=(set_iterator const &other) const
        {
            return (this->_p <= other._p);
        }
        bool				operator>(set_iterator const &other) const
        {
            return (this->_p > other._p);
        }
        bool				operator>=(set_iterator const &other) const
        {
            return (this->_p >= other._p);
        }

        operator set_iterator<const value_type, const Node> () const
        { return set_iterator<const value_type, const Node>(_p);}
    };

};

#endif