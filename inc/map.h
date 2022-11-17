//
// Created by Anisia Klimenko on 17.11.2022.
//

#ifndef MAP_H
#define MAP_H

#include "rbt.h"
#include "rbt_iterator.h"
#include "utility.h"

namespace ft {
    template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
    class map {
    public:
        typedef             Key                             key_type;
        typedef             T                               mapped_type;
        typedef             pair<const Key, T>              value_type;
        typedef             Compare                         key_compare;
        typedef             Allocator                       allocator_type;
        typedef typename    allocator_type::reference       reference;
        typedef typename    allocator_type::const_reference const_reference;
        typedef typename    allocator_type::pointer         pointer;
        typedef typename    allocator_type::const_pointer   const_pointer;
        typedef             ptrdiff_t                       difference_type;
        typedef             size_t                          size_type;

    private:
        typedef RBT<key_type, mapped_type, allocator_type, key_compare> tree_type;

    public:
        typedef RBT_Iterator<typename tree_type::node, tree_type>       iterator;
        typedef const_RBT_Iterator<typename tree_type::node, tree_type> const_iterator;
        typedef ft::reverse_iterator<iterator>                          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;

        class value_compare {
        public:
            typedef bool        result_type;
            typedef value_type  first_argument_type;
            typedef value_type  second_argument_type;

            bool operator() (const value_type &x, const value_type &y) const { return (comp(x.first, y.first)); }

        protected:
            Compare comp;
            value_compare(Compare c) : comp(c) {}

        private:
            friend class map;
        };

        explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc) {};

        template <class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type(),
            typename enable_if<!is_integral<InputIterator>::value>::type* = nullptr) : _tree(comp, alloc) {
            while (first != last) {
                _tree.insert(*first);
                first++;
            }
        }

        map (const map& x) { *this = x; };

        ~map() {
            clear();
            _tree.deallocNil();
        }

        map& operator= (const map& x) {
            clear();
            for (const_iterator first = x.begin(); first != x.end; first++) {
                _tree.insert(*first);
            }
            return *this;
        };

        iterator begin() { return _tree.begin(); };
        const_iterator begin() const { return _tree.cbegin(); };
        iterator end() { return _tree.end(); };
        const_iterator end() const { return _tree.cend(); };
//        reverse_iterator rbegin();
//        const_reverse_iterator rbegin() const;

        void clear() {
            iterator first = begin();
            while (first != end()) {
                erase(first);
                first = begin();
            }
        }

        void erase (iterator position) { _tree.erase(position->first); };
        size_type erase (const key_type& k) { return _tree.erase(k); };
        void erase (iterator first, iterator last) {
            iterator tmp = first;
            while (tmp != last) {
                tmp++;
                erase(first->first);
                first = tmp;
            }
        };

    private:
        tree_type _tree;
    };
}

#endif //MAP_H
