//
// Created by Matthos Denys on 4/23/22.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <memory>

namespace ft {
    template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
    class map {



        /*								MAP
private:

    key_compare			_comp;
    allocator_type		_alloc;
    node_alloc			_node_alloc;
    node_pointer		_root;
    node_pointer		_last;
    node_pointer		_nil;
    size_type			_size;

public:

    explicit map(const key_compare& comp, const allocator_type& alloc)
    template <class InputIterator>
    map(InputIterator first, InputIterator last, const key_compare& comp, const allocator_type& alloc)
    map(const map& x)
    virtual ~map()

    map&								operator=(const map& x)
    mapped_type&						operator[](const key_type& k)

    bool								empty() const
    size_type							size() const
    size_type							max_size() const

    iterator							begin()
    const_iterator						begin() const
    iterator							end()
    const_iterator						end() const
    reverse_iterator					rbegin()
    const_reverse_iterator				rbegin() const
    reverse_iterator					rend()
    const_reverse_iterator				rend() const

    ft::pair<iterator, bool>			insert(const value_type& val)
    iterator							insert(iterator position, const value_type& val)
    template<class InputIterator>
    void								insert(InputIterator first, InputIterator last)

    iterator							erase(iterator position)
    size_type							erase(const key_type& k)
    void								erase(iterator first, iterator last)

    iterator							find(const key_type& key)
    const_iterator						find(const key_type& key) const

    size_type							count(const key_type& k) const

    iterator							lower_bound(const key_type& k)
    const_iterator						lower_bound(const key_type& k) const
    iterator							upper_bound(const key_type& k)
    const_iterator						upper_bound(const key_type& k) const

    pair<const_iterator,const_iterator> equal_range (const key_type& k) const
    pair<iterator,iterator> 			equal_range (const key_type& k)

    void								swap(map& x)

    void								clear()

    key_compare							key_comp() const
    value_compare						value_comp() const

    allocator_type						get_allocator() const

*/

    };

    }
#endif //FT_CONTAINERS_MAP_HPP
