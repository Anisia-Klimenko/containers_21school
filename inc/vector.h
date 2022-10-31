//
// Created by Attack Cristina on 22.09.2022.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <memory>

namespace ft {

    template <typename T, typename Alloc = std::allocator<T>>
    class vector {

    public:
        typedef T       value_type;
        typedef Alloc   allocator_type;
        typedef typename    allocator_type::reference       reference;
        typedef typename    allocator_type::const_reference const_reference;
        typedef typename    allocator_type::pointer         pointer;
        typedef typename    allocator_type::const_pointer   const_pointer;

        typedef typename    iterator_traits<iterator>::difference_type  difference_type;
        typedef typename    allocator_type::size_type                   size_type;

        // constructors
        explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _begin(nullptr), _end(nullptr), _capacity(nullptr) {}
        explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
            : _alloc(alloc), _begin(nullptr), _end(nullptr), _capacity(nullptr) {
            _begin = _alloc.allocate(n);
            _capacity = _begin + n;
            _end = _begin;
            while (n--) {
                _alloc.construct(_end, val);
                _end++;
            }
        }
//        template <class InputIterator>
//        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {}
//        vector (const vector& x) : _alloc(x._alloc), _begin(x._begin), _end(x._end), _capacity(x._capacity) {}
        ~vector(void) {
            _begin.clear();
            _allocator.deallocate(_begin, capacity());
        }

//        size_type & size() const { return _size; };
//        size_type & max_size() const { return allocator_type.max_size(); };
        size_type & capacity() const { return _capacity - _begin; };

    private:
        allocator_type  _alloc;
        pointer         _begin;
        pointer         _end;
        pointer         _capacity;
//        size_t _capacity;
    };
}

#endif //VECTOR_H
