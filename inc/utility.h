//
// Created by Attack Cristina on 11/1/22.
//

#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>

namespace ft {
    template <class T1, class T2>
    struct pair {
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;
        second_type second;

        pair() : first(), second() {};
        template<class U, class V>
        pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {};
        pair (const first_type& a, const second_type& b) : first(a), second(b) {};

        // https://cplusplus.com/reference/utility/pair/operator=/
        pair& operator= (const pair& pr) {
            first = pr.first;
            second = pr.second;
            return (*this);
        };

        void swap (pair<T, T>& pr) {
            T c(a);
            a = b;
            b = c;
        }
    };

    // https://cplusplus.com/reference/utility/pair/operators/
    template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first == rhs.first && lhs.second == rhs.second; }

    template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs == rhs); }

    template <class T1, class T2>
    bool operator< (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(rhs < lhs); }

    template <class T1, class T2>
    bool operator> (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return rhs < lhs; }

    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs < rhs); }

    template <class T1, class T2> void swap (pair<T1,T2>& x, pair<T1,T2>& y) {
        T1 c(x.first);
        x.first = y.first;
        y.first = c;
        T2 d(x.second);
        x.second = y.second;
        y.second = d;
    }

    // https://cplusplus.com/reference/utility/make_pair/
    template <class T1,class T2>
    pair<T1,T2> make_pair (T1 x, T2 y) { return ( pair<T1,T2>(x,y) ); }

    // https://cplusplus.com/reference/utility/swap/
    template <class T>
    void swap ( T& a, T& b ) {
        T c(a);
        a = b;
        b = c;
    }

    // https://cplusplus.com/reference/algorithm/equal/?kw=equal
    template <class InputIterator1, class InputIterator2>
    bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
        while (first1 != last1) {
            if (!(*first1 == *first2)) return false;
            ++first1;
            ++first2;
        }
        return true;
    }
    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
        while (first1 != last1) {
            if (!pred(*first1, *first2)) return false;
            ++first1;
            ++first2;
        }
        return true;
    }

    // https://cplusplus.com/reference/algorithm/lexicographical_compare/
    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
        while (first1 != last1) {
            if (first2 == last2 || *first2 < *first1) return false;
            else if (*first1 < *first2) return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }
    template <class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) {
        while (first1 != last1) {
            if (first2 == last2 || comp(*first2, *first1)) return false;
            else if (comp(*first1, *first2)) return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }

    // https://cplusplus.com/reference/iterator/distance/
    template<class InputIterator>
    typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last) {
        typename ft::iterator_traits<InputIterator>::difference_type n = 0;
        while (first != last) {
            first++;
            n++;
        }
        return (n);
    }

    // https://cplusplus.com/reference/type_traits/enable_if/?kw=enable_if
    template<bool Cond, class T = void> struct enable_if {};
    template<class T> struct enable_if<true, T> { typedef T type; };

    // https://cplusplus.com/reference/type_traits/integral_constant/
    template <class T, T v>
    struct integral_constant {
        static constexpr T value = v;
        typedef T value_type;
        typedef integral_constant<T,v> type;
        constexpr operator T() { return v; }
    };

    // https://cplusplus.com/reference/type_traits/true_type/
    typedef integral_constant<bool, true> true_type;
    // https://cplusplus.com/reference/type_traits/false_type/
    typedef integral_constant<bool, false> false_type;

    // https://cplusplus.com/reference/type_traits/is_integral/
    template <class T> struct is_integral :                     false_type {};

    template <> struct is_integral<bool> :                      true_type {};
    template <> struct is_integral<char> :                      true_type {};
    template <> struct is_integral<char16_t> :                  true_type {};
    template <> struct is_integral<char32_t> :                  true_type {};
    template <> struct is_integral<wchar_t> :                   true_type {};
    template <> struct is_integral<signed char> :               true_type {};
    template <> struct is_integral<short int> :                 true_type {};
    template <> struct is_integral<int> :                       true_type {};
    template <> struct is_integral<long int> :                  true_type {};
    template <> struct is_integral<long long int> :             true_type {};
    template <> struct is_integral<unsigned char> :             true_type {};
    template <> struct is_integral<unsigned short int> :        true_type {};
    template <> struct is_integral<unsigned int> :              true_type {};
    template <> struct is_integral<unsigned long int> :         true_type {};
    template <> struct is_integral<unsigned long long int> :    true_type {};

}

#endif //UTILITY_H
