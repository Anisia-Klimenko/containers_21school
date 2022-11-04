//
// Created by Attack Cristina on 11/3/22.
//

#ifndef ITERATOR_H
#define ITERATOR_H

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
    bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() == rhs.base(); }
    template <class Iterator>
    bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() != rhs.base(); }
    template <class Iterator>
    bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() >= rhs.base(); }
    template <class Iterator>
    bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() <= rhs.base(); }
    template <class Iterator>
    bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() > rhs.base(); }
    template <class Iterator>
    bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() < rhs.base(); }

    // https://cplusplus.com/reference/iterator/reverse_iterator/operator_plus-free/
    template <class Iterator>
    reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) { return (rev_it + n); }
    // https://cplusplus.com/reference/iterator/reverse_iterator/operator_minus-free/
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() - rhs.base()); }
}

#endif //ITERATOR_H
