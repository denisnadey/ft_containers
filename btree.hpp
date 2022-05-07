#ifndef BTREE_H
# define BTREE_H


#include <cstddef>

namespace ft
{
    template <class value_type>
    struct s_node
    {
        typedef ft::s_node<value_type>	node;
        typedef node*					pointer;

        value_type			_data;
        pointer				_left;
        pointer				_right;
        pointer				_parent;
        bool				_color;
        int					_flag;

        s_node() :  _left(nullptr), _right(nullptr), _parent(nullptr), _color(false), _flag(0) {};

        s_node(bool flag) : _data(value_type()), _left(nullptr), _right(nullptr), _parent(nullptr), _color(false) {flag ? _flag = 1 : _flag = 2;};

        s_node(value_type data, pointer left = nullptr, pointer right = nullptr, pointer parent = nullptr, bool color = false, int flag = 0)
                : _data(data), _left(left), _right(right), _parent(parent), _color(color), _flag(flag) {};

        s_node(const node& nd) : _data(nd._data), _left(nd._left), _right(nd._right), _parent(nd._parent), _color(nd._color), _flag(nd._flag) {};

        ~s_node() {};
    };
};

#endif
