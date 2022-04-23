//
// Created by Matthos Denys on 4/23/22.
//

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

# include "vector.hpp"


namespace ft {
    template <class T, class Container = ft::vector<T> >
    class stack{
    public:
        Container   c;
        typedef             typename    Container::value_type  value_type;
        typedef                         Container              container_type;
        typedef             typename    Container::size_type   size_type;

        explicit                        stack(const container_type& cntr = container_type()) : c(cntr){};
        virtual                         ~stack(){};
        bool                            empty() const { return  c.empty(); }
        size_type			            size() const {return c.size();};
        value_type&			            top() {return c[size() - 1];};
        const value_type&	            top() const {return c.back();};
        void				            push(const value_type& val) {c.push_back(val);};
        void				            pop() {c.pop_back();};
    };
    template <class T, class Alloc>
    bool				operator==(const stack<T,Alloc>& lhs, const stack<T,Alloc>& rhs)
    {
        return lhs.size() == rhs.size() && ft::equal(lhs.c.begin(), lhs.c.end(), rhs.c.begin());
    };

    template <class T, class Alloc>
    bool				operator!=(const stack<T,Alloc>& lhs, const stack<T,Alloc>& rhs)
    {
        return lhs.size() != rhs.size() || !ft::equal(lhs.c.begin(), lhs.c.end(), rhs.c.begin());
    };

    template <class T, class Alloc>
    bool				operator<(const stack<T,Alloc>& lhs, const stack<T,Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.c.begin(), lhs.c.end(), rhs.c.begin(), rhs.c.end());
    };

    template <class T, class Alloc>
    bool				operator<=(const stack<T,Alloc>& lhs, const stack<T,Alloc>& rhs)
    {
        return !ft::lexicographical_compare(rhs.c.begin(), rhs.c.end(), lhs.c.begin(), lhs.c.end());
    };

    template <class T, class Alloc>
    bool				operator>(const stack<T,Alloc>& lhs, const stack<T,Alloc>& rhs)
    {
        return ft::lexicographical_compare(rhs.c.begin(), rhs.c.end(), lhs.c.begin(), lhs.c.end());
    };

    template <class T, class Alloc>
    bool				operator>=(const stack<T,Alloc>& lhs, const stack<T,Alloc>& rhs)
    {
        return !ft::lexicographical_compare(lhs.c.begin(), lhs.c.end(), rhs.c.begin(), rhs.c.end());
    };

}


#endif //FT_CONTAINERS_STACK_HPP
