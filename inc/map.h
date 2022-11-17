#ifndef MAP_HPP
# define MAP_HPP

#include "rbt_iterator.h"
#include "rbt.h"
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

        mapped_type& operator[] (const key_type& k) {
            iterator it = find(k);
            if (it == _tree.end()) {
                _tree.insert(ft::make_pair(k, mapped_type()));
                it = find(k);
            }
            return it->second;
        };

        mapped_type& at (const key_type& k) {
            iterator it = find(k);
            if (it == _tree.end()) {
                throw std::out_of_range("ft::map::at");
            }
            return it->second;
        };
        const mapped_type& at (const key_type& k) const {
            const_iterator it = find(k);
            if (it == _tree.end()) {
                throw std::out_of_range("ft::map::at");
            }
            return it->second;
        };

        ft::pair<iterator, bool> insert (const value_type& val) {
            typename tree_type::node *n = _tree.find(val.first);
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

        void swap (map& x) {
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

        iterator find (const key_type& k) { return iterator(_tree.find(k), _tree.getNil()); };
        const_iterator find (const key_type& k) const { return iterator(_tree.find(k), _tree.getNil()); };

        size_type count (const key_type& k) const {
            if (_tree.find(k) != _tree.getNil()) {
                return 1;
            }
            return 0;
        };

        iterator lower_bound (const key_type& k) {
            iterator it = begin();
            while (it != end() && (_tree.get_comp())((*it).first, k))
                it++;
            return (it);
        };
        const_iterator lower_bound (const key_type& k) const {
            const_iterator it = begin();
            while (it != end() && (_tree.get_comp())((*it).first, k))
                it++;
            return (it);
        };

        iterator upper_bound(const key_type &k) {
            iterator it = begin();
            while (it != end() && !((_tree.get_comp())(k, (*it).first)))
                it++;
            return (it);
        };
        const_iterator upper_bound(const key_type &k) const {
            const_iterator it = begin();
            while (it != end() && !((_tree.get_comp())(k, (*it).first)))
                it++;
            return (it);
        };

        pair<iterator, iterator> equal_range(const key_type &key) { return ft::make_pair(lower_bound(key), upper_bound(key)); };
        pair<const_iterator, const_iterator> equal_range(const key_type &key) const { return ft::make_pair(lower_bound(key), upper_bound(key)); };

        allocator_type get_allocator(void) const { return _tree.get_allocator(); };

    private:
		tree_type _tree;
	};
}

#endif
