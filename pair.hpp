#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
    template <class T1, class T2>
    struct pair
    {
        typedef	T1	first_type;
        typedef	T2	second_type;

        first_type	first;
        second_type	second;

        pair() : first(first_type()), second(second_type()) {};
        template <class U, class V>
        pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) {};
        pair(const first_type& a, const second_type& b) : first(a), second(b) {};

        pair&		operator=(const pair& pr)
        {
            first = pr.first;
            second = pr.second;
            return *this;
        }
    };

    template <class T1,class T2>
    ft::pair<T1, T2> 	make_pair(T1 x, T2 y)
    {
        return (ft::pair<T1, T2>(x, y));
    }

    template <class T1, class T2>
    bool			operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return lhs.first == rhs.first && lhs.second == lhs.second;
    }

    template <class T1, class T2>
    bool			operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class T1, class T2>
    bool			operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template <class T1, class T2>
    bool			operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return !(rhs < lhs);
    }

    template <class T1, class T2>
    bool			operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return rhs < lhs;
    }

    template <class T1, class T2>
    bool			operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return !(lhs < rhs);
    }

    template <class Arg, class Result>
    struct unary_function
    {
        typedef Arg    argument_type;
        typedef Result result_type;
    };

    template <class Arg1, class Arg2, class Result>
    struct binary_function
    {
        typedef Arg1	first_argument_type;
        typedef Arg2	second_argument_type;
        typedef Result	result_type;
    };

    template <class T>
    struct less : ft::binary_function <T,T,bool>
    {
        bool	operator()(const T& x, const T& y) const
        {
            return x < y;
        }
    };

    template <class T, class U>
    struct get_key : public unary_function<T, U>
    {
        const U &operator()(const T &x) const
        {
            return x.first;
        }
    };
};

#endif