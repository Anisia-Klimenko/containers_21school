//
// Created by Attack Cristina on 11/18/22.
//

#ifndef SET_H
#define SET_H

#include "rbt_iterator.h"
#include "rbt.h"
#include "utility.h"

namespace ft {
    template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
    class set {
    public:
        typedef             Key                             key_type;
        typedef             Key                             value_type;
        typedef             Compare                         key_compare;
        typedef             Compare                         value_compare;
        typedef             Allocator                       allocator_type;
        typedef typename    allocator_type::reference       reference;
        typedef typename    allocator_type::const_reference const_reference;
        typedef typename    allocator_type::pointer         pointer;
        typedef typename    allocator_type::const_pointer   const_pointer;
        typedef             ptrdiff_t                       difference_type;
        typedef             size_t                          size_type;

    private:
        typedef RBT_Set<key_type, key_type, allocator_type, key_compare> tree_type;

    public:
        typedef const_RBT_Iterator<typename tree_type::node, tree_type> iterator; // convertible to const
        typedef const_RBT_Iterator<typename tree_type::node, tree_type> const_iterator;
        typedef ft::reverse_iterator<iterator>                          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;

        explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
            : _tree(comp, alloc) {};

        template <class InputIterator>
        set(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type(),
			typename enable_if<!is_integral<InputIterator>::value>::type* = nullptr) : _tree(comp, alloc) {
            while (first != last) {
                _tree.insert(*first);
                first++;
            }
        };

        set (const set& x) { *this = x; };

        ~set() {
            clear();
            _tree.deallocNil();
        }

        set& operator= (const set& x) {
            clear();
            for (const_iterator first = x.begin(); first != x.end(); first++) {
                _tree.insert(*first);
            }
            return *this;
        };

        iterator begin() { return _tree.begin(); };
        const_iterator begin() const { return _tree.cbegin(); };
        iterator end() { return _tree.end(); };
        const_iterator end() const { return _tree.cend(); };

        reverse_iterator rbegin() {
            for (iterator it = begin(); it != end(); it++){
                iterator tmp = it;
                tmp++;
                if (tmp == end()) {
                    reverse_iterator temp(it);
                    return (temp);
                }
            }
            return reverse_iterator(end());
        };
        const_reverse_iterator rbegin() const {
            for (const_iterator it = begin(); it != end(); it++){
                const_iterator tmp = it;
                tmp++;
                if (tmp == end()) {
                    const_reverse_iterator temp(it);
                    return (temp);
                }
            }
        };
        reverse_iterator rend() {
            iterator it = begin();
            it--;
            reverse_iterator tmp(it);
            return tmp;
        };
        const_reverse_iterator rend() const {
            const_iterator it = begin();
            it--;
            const_reverse_iterator tmp(it);
            return tmp;
        };

        bool empty() const { return _tree.empty(); };
        size_type size() const { return _tree.size(); };
        size_type max_size() const { return _tree.max_size(); };

        pair<iterator, bool> insert (const value_type& val) {
            typename tree_type::node *n = _tree.find(val);
            if (n == _tree.getNil()) {
                n = _tree.insert(val);
                return (ft::make_pair(iterator(n, _tree.getNil()), true));
            }
            return (ft::make_pair(iterator(n, _tree.getNil()), false));
        };
        iterator insert (iterator position, const value_type& val) {
            static_cast<void>(position);
            return (iterator(_tree.insert(val), _tree.getNil()));
        };
        template <class InputIterator>
        void insert (InputIterator first, InputIterator last) {
            while (first != last) {
                _tree.insert(*first);
                first++;
            }
        };

        void erase (iterator position) { _tree.erase(*position); };
        size_type erase (const value_type& val) { return _tree.erase(val); };
        void erase (iterator first, iterator last) {
            iterator tmp = first;
            while (tmp != last) {
                tmp++;
                erase(*first);
                first = tmp;
            }
        };

        void swap (set& x) {
            tree_type temp = x._tree;
            x._tree = _tree;
            _tree = temp;
        };

        void clear() {
            iterator first = begin();
            while (first != end()) {
                erase(first);
                first = begin();
            }
        }

        key_compare key_comp() const { return _tree.get_comp(); };
        value_compare value_comp() const { return value_compare(_tree.get_comp()); };

        iterator find (const value_type& val) const { return iterator(_tree.find(val), _tree.getNil()); };

        size_type count (const value_type& val) const {
            if (_tree.find(val) != _tree.getNil()) { return 1; }
            return 0;
        };

        iterator lower_bound (const key_type& k) {
            iterator it = begin();
            while (it != end() && (_tree.get_comp())(*it, k))
                it++;
            return it;
        };
        iterator upper_bound(const key_type &k) {
            iterator it = begin();
            while (it != end() && !((_tree.get_comp())(k, *it)))
                it++;
            return it;
        };
        pair<iterator,iterator> equal_range (const value_type& val) const { return ft::make_pair(lower_bound(val),
                                                                                                 upper_bound(val)); };

        allocator_type get_allocator(void) const { return _tree.get_allocator(); };

    private:
        tree_type _tree;
    };

    template <class Key, class Compare, class Alloc>
    bool operator== ( const set<Key, Compare, Alloc>& lhs,
                     const set<Key, Compare, Alloc>& rhs ) {
        if (lhs.size() != rhs.size()) { return false; }
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    template <class Key, class Compare, class Allocator>
    bool operator!= (const set<Key, Compare, Allocator> & lhs,
                     const set<Key, Compare, Allocator> & rhs) { return !(lhs == rhs); }

    template <class Key, class Compare, class Allocator>
    bool operator<(const set<Key, Compare, Allocator>& lhs,
                   const set<Key, Compare, Allocator>& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class Key, class Compare, class Allocator>
    bool operator<=(const set<Key, Compare, Allocator>& lhs,
                    const set<Key, Compare, Allocator>& rhs) { return !(rhs < lhs); }

    template <class Key, class Compare, class Allocator>
    bool operator>(const set<Key, Compare, Allocator>& lhs,
                   const set<Key, Compare, Allocator>& rhs) { return rhs < lhs; }

    template <class Key, class Compare, class Allocator>
    bool operator>=(const set<Key, Compare, Allocator>& lhs,
                    const set<Key, Compare, Allocator>& rhs) { return !(lhs < rhs); }

    template <class Key, class Compare, class Alloc>
    void swap( ft::set<Key, Compare, Alloc>& lhs,
               ft::set<Key, Compare, Alloc>& rhs ) { lhs.swap(rhs); }
}

#endif //SET_H
