//
// Created by Attack Cristina on 11/1/22.
//

#ifndef UTILITY_H
#define UTILITY_H

#ifndef nullptr
#define nullptr 0
//#else
//#error "nullptr defined already"
#endif

#include <iostream>
#include <stddef.h>
//#include "iterator.h"

namespace ft {
    // https://cplusplus.com/reference/iterator/iterator/
    template <class Category, class T, class Distance = ptrdiff_t,
            class Pointer = T*, class Reference = T&>
    struct iterator {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };

    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : input_iterator_tag {};
    struct bidirectional_iterator_tag : forward_iterator_tag {};
    struct random_access_iterator_tag : bidirectional_iterator_tag {};

    // https://cplusplus.com/reference/iterator/iterator_traits/
    template <class Iterator>
    class iterator_traits {
    public:
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::iterator_category    iterator_category;
    };

    // https://cplusplus.com/reference/iterator/iterator_traits/
    template <class T>
    class iterator_traits<T*> {
    public:
        typedef ptrdiff_t                      difference_type;
        typedef T                              value_type;
        typedef T*                             pointer;
        typedef T&                             reference;
        typedef ft::random_access_iterator_tag iterator_category;
    };

    // https://cplusplus.com/reference/iterator/iterator_traits/
    template <class T>
    class iterator_traits<const T*> {
    public:
        typedef ptrdiff_t                      difference_type;
        typedef T                              value_type;
        typedef const T*                       pointer;
        typedef const T&                       reference;
        typedef ft::random_access_iterator_tag iterator_category;
    };

    template <typename T>
    class const_random_access_iterator;

    template <typename T>
    class random_access_iterator : public iterator<random_access_iterator_tag, T> {
    public:
        typedef typename iterator<random_access_iterator_tag, T>::value_type         value_type;
        typedef typename iterator<random_access_iterator_tag, T>::difference_type    difference_type;
        typedef typename iterator<random_access_iterator_tag, T>::pointer            pointer;
        typedef typename iterator<random_access_iterator_tag, T>::reference          reference;
        typedef typename iterator<random_access_iterator_tag, T>::iterator_category  iterator_category;

        random_access_iterator(void) : _it(nullptr) {}
        random_access_iterator(const random_access_iterator &copy) : _it(copy._it) {}
        random_access_iterator(pointer it) : _it(it) {}
        virtual ~random_access_iterator(void) {}
        random_access_iterator &operator=(const random_access_iterator &it) {
            this->_it = it._it;
            return (*this);
        }
        pointer base(void) const { return (this->_it); }
        reference operator*(void) const { return (*(this->_it)); }
        pointer operator->(void) { return (&(this->operator*())); }
        random_access_iterator operator++(int) {
            random_access_iterator temp = *this;
            this->_it++;
            return (temp);
        }
        random_access_iterator &operator++(void) {
            this->_it++;
            return (*this);
        }
        random_access_iterator operator--(int) {
            random_access_iterator temp = *this;
            this->_it--;
            return (temp);
        }
        random_access_iterator &operator--(void) {
            this->_it--;
            return (*this);
        }
        random_access_iterator operator+(difference_type n) const { return (this->_it + n); }
        random_access_iterator operator-(difference_type n) const { return (this->_it - n); }
        random_access_iterator &operator+=(difference_type n) {
            this->_it += n;
            return (*this);
        }
        random_access_iterator &operator-=(difference_type n) {
            this->_it -= n;
            return (*this);
        }
        reference operator[](difference_type n) { return (*(this->_it + n)); }
        bool operator==(const random_access_iterator<T> &rhs)               { return (this->base() == rhs.base()); }
        bool operator==(const const_random_access_iterator<const T> &rhs)   { return (this->base() == rhs.base()); }
        bool operator!=(const random_access_iterator<T> &rhs)               { return (this->base() != rhs.base()); }
        bool operator!=(const const_random_access_iterator<const T> &rhs)   { return (this->base() != rhs.base()); }
        bool operator>(const random_access_iterator<T> &rhs)                { return (this->base() > rhs.base()); }
        bool operator>(const const_random_access_iterator<const T> &rhs)    { return (this->base() > rhs.base()); }
        bool operator>=(const random_access_iterator<T> &rhs)               { return (this->base() >= rhs.base()); }
        bool operator>=(const const_random_access_iterator<const T> &rhs)   { return (this->base() >= rhs.base()); }
        bool operator<(const random_access_iterator<T> &rhs)                { return (this->base() < rhs.base()); }
        bool operator<(const const_random_access_iterator<const T> &rhs)    { return (this->base() < rhs.base()); }
        bool operator<=(const random_access_iterator<T> &rhs)               { return (this->base() <= rhs.base()); }
        bool operator<=(const const_random_access_iterator<const T> &rhs)   { return (this->base() <= rhs.base()); }

    private:
        pointer _it;
    };

    template<typename T>
    random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n,
                                        random_access_iterator<T> &it) { return (&(*it) + n); }
    template<typename T>
    random_access_iterator<T> operator+(typename const_random_access_iterator<T>::difference_type n,
                                        const_random_access_iterator<T> &it) { return (&(*it) + n); }
    template<typename T>
    typename random_access_iterator<T>::difference_type operator-(const random_access_iterator<T> &lhs,
                                                                  const random_access_iterator<T> &rhs) { return (lhs.base() - rhs.base()); }
    template<typename T>
    typename random_access_iterator<T>::difference_type operator-(const random_access_iterator<T> &lhs,
                                                                  const const_random_access_iterator<const T> &rhs) { return (lhs.base() - rhs.base()); }
    template<typename T>
    typename random_access_iterator<T>::difference_type operator-(const const_random_access_iterator<const T> &lhs,
                                                                  const random_access_iterator<T> &rhs) { return (lhs.base() - rhs.base()); }
    template<typename T>
    typename random_access_iterator<T>::difference_type operator-(const const_random_access_iterator<T> &lhs,
                                                                  const const_random_access_iterator<T> &rhs) { return (lhs.base() - rhs.base()); }

    template <typename T>
    class const_random_access_iterator : public iterator<random_access_iterator_tag, T> {
    public:
        typedef const typename  iterator<random_access_iterator_tag, T>::value_type         value_type;
        typedef typename        iterator<random_access_iterator_tag, T>::difference_type    difference_type;
        typedef typename        iterator<random_access_iterator_tag, T>::pointer            pointer;
        typedef typename        iterator<random_access_iterator_tag, T>::reference          reference;
        typedef typename        iterator<random_access_iterator_tag, T>::iterator_category  iterator_category;

        const_random_access_iterator(void) : _it(nullptr) {}
        const_random_access_iterator(const const_random_access_iterator &copy) : _it(copy._it) {}
        const_random_access_iterator(pointer it) : _it(it) {}
        template <typename U>
        const_random_access_iterator(const random_access_iterator<U> &copy) : _it(copy.base()) {}
        virtual ~const_random_access_iterator(void) {}
        const_random_access_iterator &operator=(const const_random_access_iterator &it) {
            this->_it = it._it;
            return (*this);
        }
        const_random_access_iterator &operator=(const random_access_iterator<T> &it) {
            this->_it = it.base();
            return (*this);
        }
        pointer base(void) const { return (this->_it); }
        reference operator*(void) const { return (*(this->_it)); }
        pointer operator->(void) { return (&(this->operator*())); }
        const_random_access_iterator operator++(int) {
            const_random_access_iterator temp = *this;
            this->_it++;
            return (temp);
        }
        const_random_access_iterator &operator++(void) {
            this->_it++;
            return (*this);
        }
        const_random_access_iterator operator--(int) {
            const_random_access_iterator temp = *this;
            this->_it--;
            return (temp);
        }
        const_random_access_iterator &operator--(void) {
            this->_it--;
            return (*this);
        }
        const_random_access_iterator operator+(difference_type n) const { return (this->_it + n); }
        const_random_access_iterator operator-(difference_type n) const { return (this->_it - n); }
        const_random_access_iterator &operator+=(difference_type n) {
            this->_it += n;
            return (*this);
        }
        const_random_access_iterator &operator-=(difference_type n) {
            this->_it -= n;
            return (*this);
        }
        reference operator[](difference_type n)                             { return (*(this->_it + n)); }
        bool operator==(const random_access_iterator<T> &rhs)               { return (this->base() == rhs.base()); }
        bool operator==(const const_random_access_iterator<T> &rhs)         { return (this->base() == rhs.base()); }
        bool operator!=(const random_access_iterator<T> &rhs)               { return (this->base() != rhs.base()); }
        bool operator!=(const const_random_access_iterator<T> &rhs)         { return (this->base() != rhs.base()); }
        bool operator>(const random_access_iterator<T> &rhs)                { return (this->base() > rhs.base()); }
        bool operator>(const const_random_access_iterator<T> &rhs)          { return (this->base() > rhs.base()); }
        bool operator>=(const random_access_iterator<T> &rhs)               { return (this->base() >= rhs.base()); }
        bool operator>=(const const_random_access_iterator<T> &rhs)         { return (this->base() >= rhs.base()); }
        bool operator<(const random_access_iterator<T> &rhs)                { return (this->base() < rhs.base()); }
        bool operator<(const const_random_access_iterator<T> &rhs)          { return (this->base() < rhs.base()); }
        bool operator<=(const random_access_iterator<T> &rhs)               { return (this->base() <= rhs.base()); }
        bool operator<=(const const_random_access_iterator<T> &rhs)         { return (this->base() <= rhs.base()); }

    private:
        pointer _it;
    };

    // https://cplusplus.com/reference/iterator/reverse_iterator/
    template <class Iterator>
    class reverse_iterator {
    public:
        typedef          Iterator                                           iterator_type;
        typedef typename ft::iterator_traits<Iterator>::iterator_category   iterator_category;
        typedef typename ft::iterator_traits<Iterator>::value_type          value_type;
        typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
        typedef typename ft::iterator_traits<Iterator>::pointer             pointer;
        typedef typename ft::iterator_traits<Iterator>::reference           reference;

        // https://cplusplus.com/reference/iterator/reverse_iterator/reverse_iterator/
        reverse_iterator() : _it() {};
        explicit reverse_iterator (iterator_type it) : _it(it) {};
        template <class Iter>
        reverse_iterator (const reverse_iterator<Iter>& rev_it) : _it(rev_it.base()) {};
        ~reverse_iterator() {};

        // https://cplusplus.com/reference/iterator/reverse_iterator/base/
        iterator_type base() const { return _it; };

        reverse_iterator operator= (reverse_iterator src) {
            _it = src._it;
            return (*this);
        }

        // https://cplusplus.com/reference/iterator/reverse_iterator/operator*/
        reference operator* () const { return *_it; }; // correct ?

        // https://cplusplus.com/reference/iterator/reverse_iterator/operator+/
        reverse_iterator operator+ (difference_type n) const { return reverse_iterator(_it - n); };

        // https://cplusplus.com/reference/iterator/reverse_iterator/operator++/
        reverse_iterator& operator++ () {
            _it--;
            return (*this);
        };
        reverse_iterator operator++ (int) {
            reverse_iterator temp = *this;
            ++(*this);
            return temp;
        };

        //https://cplusplus.com/reference/iterator/reverse_iterator/operator+=/
        reverse_iterator& operator+= (difference_type n) {
            (*this) = (*this) + n;
            return (*this);
        };

        // https://cplusplus.com/reference/iterator/reverse_iterator/operator-/
        reverse_iterator operator- (difference_type n) const { return reverse_iterator(_it + n); };

        // https://cplusplus.com/reference/iterator/reverse_iterator/operator--/
        reverse_iterator& operator--() {
            _it++;
            return (*this);
        };
        reverse_iterator operator--(int) {
            reverse_iterator temp = *this;
            --(*this);
            return temp;
        };

        //https://cplusplus.com/reference/iterator/reverse_iterator/operator-=/
        reverse_iterator& operator-= (difference_type n) {
            (*this) = (*this) - n;
            return (*this);
        };

        // https://cplusplus.com/reference/iterator/reverse_iterator/operator-%3E/
        pointer operator-> () const { return &(operator*()); };

        // https://cplusplus.com/reference/iterator/reverse_iterator/operator[]/
        reference operator[] (difference_type n) const { return base()[-n - 1]; };

    private:
        iterator_type _it;
    };

    // https://cplusplus.com/reference/iterator/reverse_iterator/operators/
    template <class Iterator>
    bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) { return (lhs.base() == rhs.base()); }
    template <class Iterator_L, class Iterator_R>
    bool operator==(const reverse_iterator<Iterator_L> &lhs, const reverse_iterator<Iterator_R> &rhs) { return (lhs.base() == rhs.base()); }

    template <class Iterator>
    bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) { return (lhs.base() != rhs.base()); }
    template <class Iterator_L, class Iterator_R>
    bool operator!=(const reverse_iterator<Iterator_L> &lhs, const reverse_iterator<Iterator_R> &rhs) { return (lhs.base() != rhs.base()); }

    template <class Iterator>
    bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) { return (lhs.base() > rhs.base()); }
    template <class Iterator_L, class Iterator_R>
    bool operator<(const reverse_iterator<Iterator_L> &lhs, const reverse_iterator<Iterator_R> &rhs) { return (lhs.base() > rhs.base()); }

    template <class Iterator>
    bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) { return (lhs.base() >= rhs.base()); }
    template <class Iterator_L, class Iterator_R>
    bool operator<=(const reverse_iterator<Iterator_L> &lhs, const reverse_iterator<Iterator_R> &rhs) { return (lhs.base() >= rhs.base()); }

    template <class Iterator>
    bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) { return (lhs.base() < rhs.base()); }
    template <class Iterator_L, class Iterator_R>
    bool operator>(const reverse_iterator<Iterator_L> &lhs, const reverse_iterator<Iterator_R> &rhs) { return (lhs.base() < rhs.base()); }

    template <class Iterator>
    bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) { return (lhs.base() <= rhs.base()); }
    template <class Iterator_L, class Iterator_R>
    bool operator>=(const reverse_iterator<Iterator_L> &lhs, const reverse_iterator<Iterator_R> &rhs) { return (lhs.base() <= rhs.base()); }

    // https://cplusplus.com/reference/iterator/reverse_iterator/operator_plus-free/
    template <class Iterator>
    reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) { return (rev_it + n); }
    // https://cplusplus.com/reference/iterator/reverse_iterator/operator_minus-free/
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() - rhs.base()); }

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
    // test
//    template <class T>
//    pair<T,T> make_pair (T x, T y) { return ( pair<T,T>(y,x) ); }

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
    typename ft::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last) {
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
        static const T value = v;
        typedef T value_type;
        typedef integral_constant<T,v> type;
    };

    // https://cplusplus.com/reference/type_traits/true_type/
    typedef integral_constant<bool, true> true_type;
    // https://cplusplus.com/reference/type_traits/false_type/
    typedef integral_constant<bool, false> false_type;

    // https://cplusplus.com/reference/type_traits/is_integral/
    template <class T> struct is_integral :                     false_type {};

    template <> struct is_integral<bool> :                      true_type {};
    template <> struct is_integral<char> :                      true_type {};
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
