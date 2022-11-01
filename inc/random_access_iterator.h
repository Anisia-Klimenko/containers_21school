//
// Created by Attack Cristina on 10/31/22.
//

#ifndef RANDOM_ACCESS_ITERATOR_H
#define RANDOM_ACCESS_ITERATOR_H

#include <iostream>

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
    struct forward_iterator_tag {};
    struct bidirectional_iterator_tag {};
    struct random_access_iterator_tag {};

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
        typedef typename ptrdiff_t                      difference_type;
        typedef typename T                              value_type;
        typedef typename T*                             pointer;
        typedef typename T&                             reference;
        typedef typename ft::random_access_iterator_tag iterator_category;
    };

    // https://cplusplus.com/reference/iterator/iterator_traits/
    template <class T>
    class iterator_traits<const T*> {
    public:
        typedef typename ptrdiff_t                      difference_type;
        typedef typename T                              value_type;
        typedef typename const T*                       pointer;
        typedef typename const T&                       reference;
        typedef typename ft::random_access_iterator_tag iterator_category;
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
    bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() == rhs.base(); };
    template <class Iterator>
    bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() != rhs.base(); };
    template <class Iterator>
    bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() >= rhs.base(); };
    template <class Iterator>
    bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() <= rhs.base(); };
    template <class Iterator>
    bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() > rhs.base(); };
    template <class Iterator>
    bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() < rhs.base(); };

    // https://cplusplus.com/reference/iterator/reverse_iterator/operator_plus-free/
    template <class Iterator>
    reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) { return (rev_it + n); };
    // https://cplusplus.com/reference/iterator/reverse_iterator/operator_minus-free/
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() - rhs.base()); };
}

#endif //RANDOM_ACCESS_ITERATOR_H
