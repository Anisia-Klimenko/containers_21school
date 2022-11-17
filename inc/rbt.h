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

        RBT(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
            : _size(0), _comp(comp), _alloc(alloc) {
            _nil = _node_alloc.allocate(1);
            _nil->color = BLACK;
            _nil->left = nullptr;
            _nil->right = nullptr;
            _root = _nil;
        }

        RBT(const RBT &copy) {
            *this = copy;
        }

        ~RBT() {}

        const RBT &operator=(const RBT &copy) {
            _size = copy._size;
            _root = copy._root;
            _nil = copy._nil;
            _comp = copy._comp;
            _alloc = copy._alloc;
            _node_alloc = copy._node_alloc;
            return *this;
        }

        void deallocNil() { _node_alloc.deallocate(_nil, 1); }
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

        node* insert(const value_type &val) {
            node *newNode = _node_alloc.allocate(1);
            newNode->data = _alloc.allocate(1);
            _alloc.construct(newNode->data, val);
            newNode->parent = nullptr;
            newNode->left = _nil;
            newNode->right = _nil;
            newNode->color = RED;

            node *curParent = nullptr;
            node *cur = _root;
            // check if cur is already in rbt
            while (cur != _nil) {
                curParent = cur;
                if (_comp(newNode->data->first, cur->data->first)) { cur = cur->left; }
                else if (_comp(cur->data->first, newNode->data->first)) { cur = cur->right; }
                else { return (cur); }
            }
            newNode->parent = curParent;
            if (curParent == nullptr) { _root = newNode; }
            else if (_comp(newNode->data->first, curParent->data->first)) { curParent->left = newNode; }
            else { curParent->right = newNode; }

            _size++;
            node *temp = _root;
            while (temp->right != _nil) { temp = temp->right; }
            _nil->parent = temp;
            //if newNode is the root node, recolor it to black and end
            if (newNode->parent == nullptr) {
                newNode->color = BLACK;
                return (newNode);
            }

            //if parent is root (grandparent is nullptr) then end
            if (newNode->parent->parent == nullptr)
                return (newNode);

            //fix the tree
            _fixInsert(newNode);
            return (newNode);
        }

        size_type erase(const key_type &k) {
            node *ptr = find(k);
            node *x;
            node *y;
            bool originalColor = ptr->color;

            // not found
            if (ptr == _nil) { return (0); }
            _size--;

            // ptr is root
            if (ptr == _root && _hasChildren(ptr) == false) {
                _clearNode(ptr);
                _root = _nil;
                return (1);
            }
            if (ptr->left == _nil) {
                x = ptr->right;
                _nodeTransplant(ptr, x);
            } else if (ptr->right == _nil) {
                x = ptr->left;
                _nodeTransplant(ptr, x);
            } else {
                y = _min(ptr->right);
                originalColor = y->color;
                x = y->right;
                if (y->parent == ptr) { x->parent = y; }
                else {
                    _nodeTransplant(y, x);
                    y->right = ptr->right;
                    y->right->parent = y;
                }
                _nodeTransplant(ptr, y);
                y->left = ptr->left;
                y->left->parent = y;
                y->color = ptr->color;
            }
            _clearNode(ptr);
            if (originalColor == BLACK) { _fixErase(x); }
            node *temp = _root;
            while (temp->right != _nil) { temp = temp->right; }
            _nil->parent = temp;
            return (1);
        }

        allocator_type get_allocator() const { return _alloc; }
        key_compare get_comp() const { return _comp; }
        size_type max_size() const { return _alloc.max_size(); }
        iter getNill() const { return _nil; }

        void print(void) const { _printHelper("", _root, false); }

    private:
        node*                   _root;
        node*                   _nil;
        size_type               _size;
        key_compare             _comp;
        allocator_type          _alloc;
        std::allocator<node>    _node_alloc;

        //performs left-rotation on node x
        void _leftRotate(node *x) {
            node *y = x->right;
            x->right = y->left;
            if (y->left != _nil) { y->left->parent = x; }
            y->parent = x->parent;
            if (x->parent == nullptr) { _root = y; }
            else if (x == x->parent->left) { x->parent->left = y; }
            else { x->parent->right = y; }
            y->left = x;
            x->parent = y;
        }

        //performs right-rotation on node x
        void _rightRotate(node *x) {
            node *y = x->left;
            x->left = y->right;
            if (y->right != _nil) { y->right->parent = x; }
            y->parent = x->parent;
            if (x->parent == nullptr) { _root = y; }
            else if (x == x->parent->right) { x->parent->right = y; }
            else { x->parent->left = y; }
            y->right = x;
            x->parent = y;
        }

        void _fixInsert(node *x) {
            node *y;
            while (x->parent->color == RED) {
                if (x->parent == x->parent->parent->right) {
                    y = x->parent->parent->left; //uncle of x
                    if (y->color == RED) {
                        y->color = BLACK;
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        x = x->parent->parent;
                    } else {
                        if (x == x->parent->left) {
                            x = x->parent;
                            _rightRotate(x);
                        }
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        _leftRotate(x->parent->parent);
                    }
                } else {
                    y = x->parent->parent->right; //uncle of x
                    if (y->color == RED) {
                        y->color = BLACK;
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        x = x->parent->parent;
                    } else {
                        if (x == x->parent->right) {
                            x = x->parent;
                            _leftRotate(x);
                        }
                        x->parent->color = BLACK;
                        x->parent->parent->color = RED;
                        _rightRotate(x->parent->parent);
                    }
                }
                if (x == _root)
                    break ;
            }
            _root->color = BLACK;
        }

        void _clearNode(node *n) {
            _alloc.deallocate(n->data, 1);
            _node_alloc.deallocate(n, 1);
        }

        bool _hasChildren(node *n) const {
            if (n->left == _nil && n->right == _nil) { return (false); }
            return (true);
        }

        //replaces node x with node y
        void _nodeTransplant(node *x, node *y) {
            if (x->parent == nullptr) { _root = y; }
            else if (x == x->parent->left) { x->parent->left = y; }
            else { x->parent->right = y; }
            y->parent = x->parent;
        }

        //returns pointer to node with the smallest key (left-most in the tree)
        node *_min(node *ptr) {
            while (ptr->left != _nil) { ptr = ptr->left; }
            return (ptr);
        }

        void _fixErase(node *x) {
            node *y;
            while (x != _root && x->color == BLACK) {
                if (x == x->parent->left) {
                    y = x->parent->right;
                    if (y->color == RED) {
                        y->color = BLACK;
                        x->parent->color = RED;
                        _leftRotate(x->parent);
                        y = x->parent->right;
                    }
                    if (y->left->color == BLACK && y->right->color == BLACK) {
                        y->color = RED;
                        x = x->parent;
                    } else {
                        if (y->right->color == BLACK) {
                            y->left->color = BLACK;
                            y->color = RED;
                            _rightRotate(y);
                            y = x->parent->right;
                        }
                        y->color = x->parent->color;
                        x->parent->color = BLACK;
                        y->right->color = BLACK;
                        _leftRotate(x->parent);
                        x = _root;
                    }
                } else {
                    y = x->parent->left;
                    if (y->color == RED) {
                        y->color = BLACK;
                        x->parent->color = RED;
                        _rightRotate(x->parent);
                        y = x->parent->left;
                    }
                    if (y->right->color == BLACK && y->left->color == BLACK) {
                        y->color = RED;
                        x = x->parent;
                    } else {
                        if (y->left->color == BLACK) {
                            y->right->color = BLACK;
                            y->color = RED;
                            _leftRotate(y);
                            y = x->parent->left;
                        }
                        y->color = x->parent->color;
                        x->parent->color = BLACK;
                        y->left->color = BLACK;
                        _rightRotate(x->parent);
                        x = _root;
                    }
                }
            }
            x->color = BLACK;
        }

        void _printHelper(const std::string& prefix, const node* n, bool isLeft) const {
            if (n != _nil && n != nullptr) {
                std::cout << prefix;
                std::cout << (isLeft ? "├──" : "└──" );

                // print the value of the node
                std::cout << n->data->first << std::endl;

                // enter the next tree level - left and right branch
                _printHelper(prefix + (isLeft ? "│   " : "    "), n->left, true);
                _printHelper(prefix + (isLeft ? "│   " : "    "), n->right, false);
            }
        }
    };
}

#endif //RBT_H
