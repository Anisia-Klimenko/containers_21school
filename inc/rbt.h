//
// Created by Attack Cristina on 11/16/22.
//

#ifndef RBT_H
#define RBT_H

#include <iostream>
#include <memory>

#define BLACK false
#define RED true

namespace ft {
    template <typename Key, typename T,
            class Alloc = std::allocator<pair<const Key, T> >, class Compare = std::less<Key> >
    class RBT {
    public:

        struct node;

        typedef             Key                                     key_type;
        typedef             T                                       mapped_type;
        typedef             ft::pair<const key_type, mapped_type>   value_type;
        typedef             Alloc                                   allocator_type;
        typedef             Compare                                 key_compare;
        typedef typename    allocator_type::reference               reference;
        typedef typename    allocator_type::const_reference         const_reference;
        typedef typename    allocator_type::pointer                 pointer;
        typedef typename    allocator_type::const_pointer           const_pointer;
        typedef             ptrdiff_t                               difference_type;
        typedef             size_t                                  size_type;
        typedef             node*                                   iter;
        typedef const       node*                                   const_iter;

        struct node {
            pointer data;
            node*   left;
            node*   right;
            node*   parent;
            bool    color;
        };

        RBT(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _size(0), _comp(comp), _alloc(alloc) {
            _nil = _node_alloc.allocate(1);
            _nil->color = BLACK;
            _nil->left = nullptr;
            _nil->right = nullptr;
            _root = _nil;
        }

        ~RBT() {
            _node_alloc.deallocate(_nil, 1);
        }

        size_type size() const { return _size; }
        bool empty() const { return (_size == 0); }

        node* find(const key_type& key) const {
            node* cur = _root;

            while (cur != _nil) {
                if (cur->data->first == key) {
                    break;
                } else if (_comp(cur->data->first, key)) {
                    cur = cur->left;
                } else {
                    cur = cur->right;
                }
            }

            return cur;
        }



    private:
        node*                   _root;
        node*                   _nil;
        size_type               _size;
        key_compare             _comp;
        allocator_type          _alloc;
        std::allocator<node>    _node_alloc;
    };
}

#endif //RBT_H
