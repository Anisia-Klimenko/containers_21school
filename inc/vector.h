//
// Created by Attack Cristina on 22.09.2022.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <memory>
#include "iterator.h"
#include "utility.h"

namespace ft {

    template <typename T, typename Alloc = std::allocator<T>>
    class vector {

    public:
        typedef             T                                           value_type;
        typedef             Alloc                                       allocator_type;
        typedef typename    allocator_type::reference                   reference;
        typedef typename    allocator_type::const_reference             const_reference;
        typedef typename    allocator_type::pointer                     pointer;
        typedef typename    allocator_type::const_pointer               const_pointer;
        typedef typename    ft::random_access_iterator<T>               iterator;
        typedef typename    ft::const_random_access_iterator<const T>   const_iterator;
        typedef typename    ft::reverse_iterator<iterator>              reverse_iterator;
        typedef typename    ft::reverse_iterator<const_iterator>        const_reverse_iterator;
        typedef typename    iterator_traits<iterator>::difference_type  difference_type;
        typedef typename    allocator_type::size_type                   size_type;

        // constructors
        explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _begin(nullptr), _end(nullptr), _capacity(0) {}
        explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
            : _alloc(alloc), _begin(nullptr), _end(nullptr), _capacity(0) {
            _begin = _alloc.allocate(n);
            _capacity = n;
            _end = _begin;
            while (n--) {
                try {
                    _alloc.construct(_end, val);
                    _end++;
                } catch (...) {
                    pointer tmp = _begin;
                    while (tmp != _end) {
                        _alloc.destroy(tmp);
                        tmp++;
                    }
                    _alloc.deallocate(_begin, _capacity);
                    throw ;
                }
            }
        }
        template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {
            difference_type n = ft::distance(first, last);
            _begin = _alloc.allocate(n);
            _capacity = n;
            _end = _begin;
            while (first != last) {
                try {
                    _alloc.construct(_end, val);
                    _end++;
                    first++;
                } catch (...) {
                    pointer tmp = _begin;
                    while (tmp != _end) {
                        _alloc.destroy(tmp);
                        tmp++;
                    }
                    _alloc.deallocate(_begin, _capacity);
                    throw ;
                }
            }
        }
        vector (const vector& x) : _alloc(x._alloc), _begin(nullptr), _end(nullptr), _capacity(0) {
            // insert (?)
        }
        ~vector() {
            clear();
            _allocator.deallocate(_begin, capacity());
        }

        vector& operator= (const vector& x) {
            if (*this == x) { return *this; }
            clear();
//            pointer copy = _alloc.allocate(x._capacity);
            // insert (?)
        }

        iterator begin() { return _begin; };
        const_iterator begin() const { return const_iterator(_begin); };

        iterator end() { return _end; };
        const_iterator end() const { return const_iterator(_end); };

        reverse_iterator rbegin() { return reverse_iterator(_begin + size() - 1)};
        const_reverse_iterator rbegin() const { return const_reverse_iterator(_begin + size() - 1); };

        reverse_iterator rend() { return reverse_iterator(_begin - 1)};
        const_reverse_iterator rend() const { return const_reverse_iterator(_begin - 1); };

        // without noexept (c++11)
        const_iterator cbegin() const { return const_iterator(_begin); };
        const_iterator cend() const { return const_iterator(_end); };
        const_reverse_iterator crbegin() const { return const_reverse_iterator(_begin + size() - 1); };
        const_reverse_iterator crend() const { return const_reverse_iterator(_begin - 1); };

        size_type size() const { return _end - _begin; };
        size_type max_size() const { return _alloc.max_size(); };

        void resize (size_type n, value_type val = value_type()) {
            if (n < size()) {
                pointer tmp = _begin + n;
                while (tmp != _end) {
                    _alloc.destroy(tmp);
                    tmp++;
                }
            } else if (n > max_size()) {
                throw std::bad_alloc("ft::vector::resize");
            } else if (n > size() && n <= max_size()) {
                // insert (?)
            }
        };

        size_type & capacity() const { return _capacity; };
        bool empty() const { return (size() == 0); };

        void reserve (size_type n) {
            if (n > max_size()) { throw std::length_error("ft::vector::reserve"); }
            if (n > _capacity && n <= max_size()) {
                pointer prev_begin = _begin;
                size_type prev_capacity = _capacity;
                size_type count = 0;

                _begin = _alloc.allocate(n);
                _end = _begin;
                while (count < n) {
                    try {
                        _alloc.construct(_end, *(prev_begin + count));
                        _end++;
                        count++
                    } catch (...) {
                        pointer tmp = _begin;
                        while (tmp != _end) {
                            _alloc.destroy(tmp);
                            tmp++;
                        }
                        _alloc.deallocate(_begin, _capacity);
                        throw ;
                    }
                }
                _alloc.deallocate(prev_begin, prev_capacity);
                _capacity = n;
            }
        };

        void shrink_to_fit() {
            if (_capacity > size()) {
                pointer prev_begin = _begin;
                size_type prev_capacity = _capacity;
                size_type size = size();
                size_type count = 0;

                _begin = _alloc.allocate(size);
                _end = _begin;
                while (count < size) {
                    try {
                        _alloc.construct(_end, *(prev_begin + count));
                        _end++;
                        count++;
                    } catch (...) {
                        pointer tmp = _begin;
                        while (tmp != _end) {
                            _alloc.destroy(tmp);
                            tmp++;
                        }
                        _alloc.deallocate(_begin, _capacity);
                        throw ;
                    }
                }
                _capacity = size;
                count = 0;
                while (count < size) {
                    _alloc.destroy(prev_begin + count);
                    count++;
                }
                _alloc.deallocate(prev_begin, prev_capacity);
            }
        }

        reference operator[] (size_type n) { return *(_begin + n); };
        const_reference operator[] (size_type n) const { return *(_begin + n); };

        reference at (size_type n) {
            if (n >= size()) { throw std::out_of_range("ft::vector::at"); }
            return (*this[n]);
        };
        const_reference at (size_type n) const {
            if (n >= size()) { throw std::out_of_range("ft::vector::at"); }
            return (*this[n]);
        };

        reference front() { return *_begin; };
        const_reference front() const { return *_begin; };

        reference back() { return *(_end - 1); };
        const_reference back() const { return *(_end - 1); };

        value_type* data() { return _begin; };
        const value_type* data() const { return _begin; };

        allocator_type get_allocator() const { return _alloc; };

        void clear(void) {
            size_type size = size();
            for (size_type i = 0; i < size; i++) {
                _end--;
                _alloc.destroy(_end);
            }
        }


    private:
        allocator_type  _alloc;
        pointer         _begin;
        pointer         _end;
        size_type       _capacity;
    };
}

#endif //VECTOR_H
