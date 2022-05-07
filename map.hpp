#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include "utils.hpp"
# include "pair.hpp"
# include "btree.hpp"
# include "map_iterator.hpp"

# define RED true
# define BLACK false



namespace ft
{
    template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
    class map
    {
    public:
        typedef				Key													key_type;
        typedef				const Key										const_key_type;
        typedef				T													mapped_type;
        typedef				ft::pair<const key_type, mapped_type>				value_type;
        typedef				Compare												key_compare;
        typedef				Alloc												allocator_type;
        typedef	typename	allocator_type::reference							reference;
        typedef	typename	allocator_type::const_reference						const_reference;
        typedef	typename	allocator_type::pointer								pointer;
        typedef	typename	allocator_type::const_pointer						const_pointer;

        typedef				ft::s_node<value_type>								node_type;
        typedef			 	node_type*											node_pointer;
        typedef	typename	std::allocator<node_type>							node_alloc;

        typedef	typename	ft::map_iterator<value_type, node_type>				iterator;
        typedef	typename	ft::map_iterator<const value_type, const node_type>	const_iterator;
        typedef	typename	ft::reverse_iterator<iterator>						reverse_iterator;
        typedef	typename	ft::reverse_iterator<const_iterator>				const_reverse_iterator;

        typedef	typename	ft::iterator_traits<iterator>::difference_type	difference_type;
        typedef				size_t											size_type;

        class value_compare : binary_function<value_type,value_type,bool>
        {
            friend class map;
        protected:
            Compare comp;
            value_compare (Compare c) : comp(c) {}
        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator() (const value_type& x, const value_type& y) const
            {
                return comp(x.first, y.first);
            }
        };

    private:

        key_compare			_comp;
        allocator_type		_alloc;
        node_alloc			_node_alloc;
        node_pointer		_root;
        node_pointer		_last;
        node_pointer		_nil;
        size_type			_size;

    public:

        explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
                : _comp(comp), _alloc(alloc), _node_alloc(node_alloc()), _root(nullptr), _size(0)
        {
            _last = _node_alloc.allocate(sizeof(node_type));
            _nil = _node_alloc.allocate(sizeof(node_type));
            _node_alloc.construct(_last, node_type(true));
            _node_alloc.construct(_nil, node_type(false));
        }

        template <class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
                : _comp(comp), _alloc(alloc), _node_alloc(node_alloc()), _root(nullptr), _size(0)
        {
            _last = _node_alloc.allocate(sizeof(node_type));
            _nil = _node_alloc.allocate(sizeof(node_type));
            _node_alloc.construct(_last, node_type(true));
            _node_alloc.construct(_nil, node_type(false));
            insert(first, last);
        };

        map(const map& x) : _comp(x._comp), _alloc(x._alloc), _node_alloc(x._node_alloc), _root(nullptr), _last(x._last), _nil(x._nil), _size(0)
        {
            const_iterator	first = x.begin();
            const_iterator	last = x.end();
            insert(first, last);
        };

        virtual ~map()
        {
            clear();
            _node_alloc.destroy(_last);
            _node_alloc.destroy(_nil);
        };

        map&						operator=(const map& x)
        {
            _alloc = x._alloc;
            _node_alloc = x._node_alloc;
            _comp = x._comp;
            _root = nullptr;
            const_iterator	first = x.begin();
            const_iterator	last = x.end();
            insert(first, last);
            return *this;
        }

/* ELEMENT ACCESS */

        mapped_type&				operator[](const key_type& k)
        {
            return insert(ft::make_pair(k, mapped_type())).first->second;
        }

/* CAPACITY */

        bool						empty() const
        {
            return _size == 0;
        }

        size_type					size() const
        {
            return _size;
        }

        size_type					max_size() const
        {
            return std::numeric_limits<size_type>::max() / sizeof(s_node<value_type>);
        }


/* ITERATORS */

        iterator					begin()
        {
            return far_left(_root);
        }
        const_iterator				begin() const
        {
            return far_left(_root);
        }
        iterator					end()
        {
            return _last;
        }
        const_iterator				end() const
        {
            return _last;
        }
        reverse_iterator			rbegin()
        {
            return reverse_iterator(far_right(_root));
        }
        const_reverse_iterator		rbegin() const
        {
            return reverse_iterator(far_right(_root));
        }
        reverse_iterator			rend()
        {
            return reverse_iterator(_last);
        }
        const_reverse_iterator		rend() const
        {
            return 	reverse_iterator(_last);
        }



/* MODIFIERS */

        ft::pair<iterator, bool>	insert(const value_type& val)
        {
            iterator	tmp = this->find(val.first);
            if (tmp == _last)
            {
                return pair<iterator, bool>(insert_in_tree(val, _root), true);
            }
            return pair<iterator, bool>(tmp, false);
        }

        iterator					insert(iterator position, const value_type& val)
        {
            (void)position;
            return insert(val).first;
        }

        template<class InputIterator>
        void						insert(InputIterator first, InputIterator last)
        {
            for (InputIterator it = first; it != last; ++it)
                insert(*it);
        }

        iterator					erase(iterator position)
        {
            iterator	it = find(position->first);
            iterator	res = it - 1;
            if (it != _last)
                delete_node(it.base());
            if (res.base() == _last)
                return (begin());
            return res;
        }

        size_type					erase(const key_type& k)
        {
            iterator	it = find(k);
            if (it != _last)
            {
                delete_node(it.base());
                return 1;
            }
            return 0;
        }

        void						erase(iterator first, iterator last)
        {
            iterator	it = first;
            while (it != last)
                it = erase(it);
        }

        void						swap(map& x)
        {
            map	tmp = x;
            x.clear();
            x.insert(begin(), end());
            this->clear();
            this->insert(tmp.begin(), tmp.end());
        }

        void						clear()
        {
            while (_size != 0)
                erase (far_left(_root));
        }

/* OBSERVERS */

        key_compare					key_comp() const
        {
            return _comp;
        }

        value_compare				value_comp() const
        {
            return value_compare(_comp);
        }

/* OPERATIONS */

        iterator					find(const key_type& key)
        {
            node_pointer	node = _root;

            if (_size == 0)
                return _last;
            while (!(!_comp(key, node->_data.first) && !_comp(node->_data.first, key)) && node->_flag == 0)
            {
                if (_comp(key, node->_data.first))
                    node = node->_left;
                else
                    node = node->_right;
            }
            if (node->_flag == 0)
                return iterator(node);
            return _last;
        }

        const_iterator				find(const key_type& key) const
        {
            node_pointer	node = _root;

            if (_size == 0)
                return _last;
            while (!(!_comp(key, node->_data.first) && !_comp(node->_data.first, key)) && node->_flag == 0)
            {
                if (_comp(key, node->_data.first))
                    node = node->_left;
                else
                    node = node->_right;
            }
            if (node->_flag == 0)
                return iterator(node);
            return _last;
        }

        size_type					count(const key_type& k) const
        {
            const_iterator	it = find(k);
            if (it.base() != _last)
                return 1;
            return 0;
        }

        iterator					lower_bound(const key_type& k)
        {
            iterator	it = begin();
            while (it.base()!= _last && _comp(it->first, k) == true)
                ++it;
            return it;
        }

        const_iterator				lower_bound(const key_type& k) const
        {
            const_iterator	it = begin();
            while (it.base() != _last && _comp(it->first, k) == true)
                ++it;
            return it;
        }

        iterator					upper_bound(const key_type& k)
        {
            iterator	it = begin();
            while (it.base() != _last && _comp(k, it->first) == false)
                ++it;
            return it;
        }

        const_iterator				upper_bound(const key_type& k) const
        {
            const_iterator	it = begin();
            while (it.base() != _last && _comp(k, it->first) == false)
                ++it;
            return it;
        }

        pair<const_iterator,const_iterator> equal_range (const key_type& k) const
        {
            return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
        }

        pair<iterator,iterator> equal_range (const key_type& k)
        {
            return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
        }

        allocator_type				get_allocator() const
        {
            return _alloc;
        }



    private:

        node_pointer				far_left(node_pointer node) const /// крайний слева
        {
            if (!node)
                return _last;
            while (node->_left->_flag == 0)
                node = node->_left;
            return node;
        }

        node_pointer				far_right(node_pointer node) const  /// крайний справа
        {
            if (!node)
                return _last;
            while (node->_right->_flag == 0)
                node = node->_right;
            return node;
        }

        void						left_rotate(node_pointer a)  /// левый поворот
        {
            node_pointer	b = a->_right;
            a->_right = b->_left;
            if (b->_left->_flag == 0)
                b->_left->_parent = a;
            if (b->_flag == 0)
                b->_parent = a->_parent;
            if (a->_parent)
            {
                if (a == a->_parent->_left)
                    a->_parent->_left = b;
                else
                    a->_parent->_right = b;
            }
            else
                _root = b;
            b->_left = a;
            if (a->_flag == 0)
                a->_parent = b;
        }

        void						right_rotate(node_pointer a) /// правый поворот
        {
            node_pointer	b = a->_left;
            a->_left = b->_right;
            if (b->_right->_flag == 0)
                b->_right->_parent = a;
            if (b->_flag == 0)
                b->_parent = a->_parent;
            if (a->_parent)
            {
                if (a == a->_parent->_right)
                    a->_parent->_right = b;
                else
                    a->_parent->_left = b;
            }
            else
                _root = b;
            b->_right = a;
            if (a->_flag == 0)
                a->_parent = b;
        }

        node_pointer				insert_in_tree(const value_type& val, node_pointer current) /// вставка в дерево
        {
            if (_size == 0)
            {
                node_pointer	new_node = new node_type(val, _nil, _last, nullptr, BLACK, 0);
                _root = new_node;
                ++_size;
                return _root;
            }
            if (_comp(val.first, current->_data.first) && current->_left->_flag == 0)
                return insert_in_tree(val, current->_left);
            if (!_comp(val.first, current->_data.first) && current->_right->_flag == 0)
                return insert_in_tree(val, current->_right);

            node_pointer	new_node = new node_type(val, _nil, _nil, current, RED, 0);

            if (_comp(val.first, current->_data.first))
                current->_left = new_node;
            else
                current->_right = new_node;
            ++_size;
            far_left(_root)->_left = _last;
            far_right(_root)->_right = _last;
            balance(new_node);

            return new_node;
        }

        bool					is_left_branch(node_pointer	node) /// левая ветвь
        {
            if (!node->_parent)
                return false;
            return node == node->_parent->_left;
        }

        void					balance(node_pointer x) /// балансировка
        {
            while (x != _root && x->_parent->_color == RED)
            {
                if (is_left_branch(x->_parent))
                {
                    node_pointer	uncle = x->_parent->_parent->_right;
                    node_pointer	gf = x->_parent->_parent;
                    node_pointer	dad = x->_parent;
                    if (uncle->_color == RED)
                    {
                        dad->_color = BLACK;
                        uncle->_color = BLACK;
                        gf->_color = RED;
                        x = gf;
                    }
                    else
                    {
                        if (!is_left_branch(x))
                        {
                            x = dad;
                            left_rotate(x);
                        }
                        x->_parent->_color = BLACK;
                        x->_parent->_parent->_color = RED;
                        right_rotate(x->_parent->_parent);
                    }
                }
                else
                {
                    node_pointer	uncle = x->_parent->_parent->_left;
                    node_pointer	gf = x->_parent->_parent;
                    node_pointer	dad = x->_parent;
                    if (uncle->_color == RED)
                    {
                        dad->_color = BLACK;
                        uncle->_color = BLACK;
                        gf->_color = RED;
                        x = gf;
                    }
                    else
                    {
                        if (is_left_branch(x))
                        {
                            x = dad;
                            right_rotate(x);
                        }
                        x->_parent->_color = BLACK;
                        x->_parent->_parent->_color = RED;
                        left_rotate(x->_parent->_parent);
                    }
                }
            }
            _root->_color = BLACK;
        }

        void	balance_after_del(node_pointer node)  /// балансировка после удаления
        {
            while (node->_parent && node != _root && node->_color == BLACK)
            {
                if (is_left_branch(node))
                {
                    node_pointer	bro = node->_parent->_right;
                    if (bro->_color == RED)
                    {
                        bro->_color = BLACK;
                        node->_parent->_color = RED;
                        left_rotate(node->_parent);
                        bro = node->_parent->_right;
                    }
                    if (bro->_left->_color == BLACK && bro->_right->_color == BLACK)
                    {
                        bro->_color = RED;
                        node = node->_parent;
                    }
                    else
                    {
                        if (bro->_right->_color == BLACK)
                        {
                            bro->_left->_color = BLACK;
                            bro->_color = RED;
                            right_rotate(bro);
                            bro = node->_parent->_right;
                        }
                        bro->_color = node->_parent->_color;
                        node->_parent->_color = BLACK;
                        bro->_right->_color = BLACK;
                        left_rotate(node->_parent);
                        node =_root;
                    }
                }
                else
                {
                    node_pointer	bro = node->_parent->_left;
                    if (bro->_color == RED)
                    {
                        bro->_color = BLACK;
                        node->_parent->_color = RED;
                        right_rotate(node->_parent);
                        bro = node->_parent->_left;
                    }
                    if (bro->_right->_color == BLACK && bro->_left->_color == BLACK)
                    {
                        bro->_color = RED;
                        node = node->_parent;
                    }
                    else
                    {
                        if (bro->_left->_color == BLACK)
                        {
                            bro->_right->_color = BLACK;
                            bro->_color = RED;
                            left_rotate(bro);
                            bro = node->_parent->_left;
                        }
                        bro->_color = node->_parent->_color;
                        node->_parent->_color = BLACK;
                        bro->_left->_color = BLACK;
                        right_rotate(node->_parent);
                        node = _root;
                    }
                }
            }
            node->_color = BLACK;
        }

        void	delete_0_child(node_pointer node)
        {
            if (node != _root)
            {
                if (is_left_branch(node))
                    node->_parent->_left = _nil;
                else
                    node->_parent->_right = _nil;
            }
            --_size;
            _nil->_parent = node->_parent;
            if (node->_color == BLACK && _size > 1)
                balance_after_del(_nil);
            _nil->_parent = nullptr;
            if (_size == 0)
                _root = nullptr;
            _node_alloc.destroy(node);
        }

        void	delete_1_child(node_pointer node, bool left)
        {
            if (node == _root)
            {
                if (left)
                    _root = node->_left;
                else
                    _root = node->_right;
                _root->_parent = nullptr;
            }
            else
            {
                if (is_left_branch(node))
                    node->_parent->_left = (left ? node->_left : node->_right);
                else
                    node->_parent->_right = (left ? node->_left : node->_right);
            }
            if (left)
                node->_left->_parent = node->_parent;
            else
                node->_right->_parent = node->_parent;
            --_size;
            if (node->_color == BLACK)
            {
                if (left)
                    balance_after_del(node->_left);
                else
                    balance_after_del(node->_right);
            }
            _node_alloc.destroy(node);

        }

        void	delete_2_child(node_pointer node)
        {
            node_pointer	node1 = far_left(node->_right);

            pair<key_type, mapped_type > & a =
                    (pair<key_type, mapped_type>&)(node->_data);
            pair<key_type, mapped_type>& b =
                    (pair<key_type, mapped_type>&)(node1->_data);
            std::swap(a, b);
            delete_node(node1);
        }
        void	delete_node(node_pointer node)
        {
            if (node->_left->_flag != 0 && node->_right->_flag != 0)
                delete_0_child(node);
            else if (node->_left->_flag == 0 && node->_right->_flag == 0)
                delete_2_child(node);
            else
                delete_1_child(node, node->_left->_flag == 0);
            if (_size)
            {
                far_left(_root)->_left = _last;
                far_right(_root)->_right = _last;
            }
        }
    };
};


#endif