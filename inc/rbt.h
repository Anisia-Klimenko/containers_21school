#ifndef RBT_HPP
# define RBT_HPP

#include <iostream>
#include <memory>
#include "utility.h"
#include "rbt_iterator.h"

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

        RBT(const RBT &copy) { *this = copy; }

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

		//inserts element, fixes the tree and returns pointer to inserted element
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

        node* find(const key_type& key) const {
            node* cur = _root;
            while (cur != _nil) {
                if (cur->data->first == key) {
                    break;
                } else if (_comp(key, cur->data->first)) {
                    cur = cur->left;
                } else {
                    cur = cur->right;
                }
            }
            return cur;
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

        void print(void) const { _printHelper("", _root, false); }

        allocator_type get_allocator() const { return _alloc; }
        key_compare get_comp() const { return _comp; }
        size_type max_size() const { return _alloc.max_size() / 2; } // bad move
        iter getNil() const { return _nil; }

        RBT_Iterator<node, RBT> begin(void) {
            iter temp = _root;
            while (temp != _nil && temp->left != _nil)
                temp = temp->left;
            return (RBT_Iterator<node, RBT>(temp, _nil));
        }
        const_RBT_Iterator<node, RBT> cbegin(void) const {
            iter temp = _root;
            while (temp != _nil && temp->left != _nil)
                temp = temp->left;
            return (const_RBT_Iterator<node, RBT>(temp, _nil));
        }

        RBT_Iterator<node, RBT> end(void) {
            return (RBT_Iterator<node, RBT>(_nil, _nil));
        }
        const_RBT_Iterator<node, RBT> cend(void) const {
            return (const_RBT_Iterator<node, RBT>(_nil, _nil));
        }

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
                std::cout << (isLeft ? "?????????" : "?????????" );
                // print the value of the node
                std::cout << n->data->first << std::endl;
                // enter the next tree level - left and right branch
                _printHelper(prefix + (isLeft ? "???   " : "    "), n->left, true);
                _printHelper(prefix + (isLeft ? "???   " : "    "), n->right, false);
            }
        }
	};

	// RBT above relies on using pairs, so this is just a copy-pasted class with minor changes
	template <typename Key, typename T, class Alloc = std::allocator<T>, class Compare = std::less<T> >
	class RBT_Set {
	public:
		struct node;

		typedef             Key                             key_type;
		typedef             T                               mapped_type;
		typedef             Key                             value_type;
		typedef             Alloc                           allocator_type;
		typedef typename    allocator_type::reference       reference;
		typedef typename    allocator_type::const_reference const_reference;
		typedef typename    allocator_type::pointer         pointer;
		typedef typename    allocator_type::const_pointer   const_pointer;
		typedef             ptrdiff_t                       difference_type;
		typedef             size_t                          size_type;
		typedef             node*                           iter;
		typedef const       node*                           const_iter;
		typedef             Compare                         key_compare;

		struct node {
			pointer data;
			node *parent;
			node *left;
			node *right;
			bool color;
		};

		RBT_Set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _size(0), _comp(comp), _alloc(alloc) {
			_nil = _node_alloc.allocate(1);
			_nil->color = BLACK;
			_nil->left = nullptr;
			_nil->right = nullptr;
			_root = _nil;
		}

		RBT_Set(const RBT_Set &copy) { *this = copy; }

		~RBT_Set(void) {}

		const RBT_Set &operator=(const RBT_Set &copy) {
			_size = copy._size;
			_root = copy._root;
			_nil = copy._nil;
			_comp = copy._comp;
			_alloc = copy._alloc;
			_node_alloc = copy._node_alloc;
			return *this;
		}

		void deallocNil(void) { _node_alloc.deallocate(_nil, 1); }
        size_type size(void) const { return _size; }
        bool empty(void) const { return (_size == 0); }

		//inserts element, fixes the tree and returns pointer to inserted element
		node *insert(const value_type &val) {
			node *n = _node_alloc.allocate(1);
			n->data = _alloc.allocate(1);
			_alloc.construct(n->data, val);
			n->parent = nullptr;
			n->left = _nil;
			n->right = _nil;
			n->color = RED;

			node *y = nullptr;
			node *x = _root;
			while (x != _nil) {
				y = x;
				if (_comp(*n->data, *x->data)) { x = x->left; }
				else if (_comp(*x->data, *n->data)) { x = x->right; }
				else { return x; }
			}
			n->parent = y;
			if (y == nullptr) { _root = n; }
			else if (_comp(*n->data, *y->data)) { y->left = n; }
			else { y->right = n; }

			_size++;
			node *temp = _root;
			while (temp->right != _nil)
				temp = temp->right;
			_nil->parent = temp;
			//if n is the root node, recolor it to black and end
			if (n->parent == nullptr) {
				n->color = BLACK;
				return n;
			}

			//if parent is root (grandparent is nullptr) then end
			if (n->parent->parent == nullptr) { return n; }

			//fix the tree
			_fixInsert(n);
			return n;
		}

		//inserts element, fixes the tree and returns pointer to inserted element
		node *insert(const key_type &key, const mapped_type &val) { return (insert(make_pair(key, val))); }

        node *find(const key_type &key) const {
            node *n = _root;
            while (n != _nil) {
                if (*n->data == key) { break ; }
                if (_comp(key, *n->data)) { n = n->left; }
                else { n = n->right; }
            }
            return n;
		}

		size_type erase(const key_type &k) {
			node *ptr = find(k);
			node *x;
			node *y;
			bool originalColor = ptr->color;

			if (ptr == _nil) { return 0; }
			_size--;
			if (ptr == _root && _hasChildren(ptr) == false) {
				_clearNode(ptr);
				_root = _nil;
				return 1;
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
				if (y->parent == ptr) {
                    x->parent = y;
                } else {
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
			return 1;
		}

		void print(void) const { _printHelper("", _root, false); }
		allocator_type get_allocator(void) const { return _alloc; }
		key_compare get_comp(void) const { return _comp; }

		//for iterators
		RBT_Iterator<node, RBT_Set> begin(void) {
			iter temp = _root;
			while (temp != _nil && temp->left != _nil) { temp = temp->left; }
			return RBT_Iterator<node, RBT_Set>(temp, _nil);
		}
		const_RBT_Iterator<node, RBT_Set> cbegin(void) const {
			iter temp = _root;
			while (temp != _nil && temp->left != _nil) { temp = temp->left; }
			return const_RBT_Iterator<node, RBT_Set>(temp, _nil);
		}

		RBT_Iterator<node, RBT_Set> end(void) { return RBT_Iterator<node, RBT_Set>(_nil, _nil); }
		const_RBT_Iterator<node, RBT_Set> cend(void) const { return const_RBT_Iterator<node, RBT_Set>(_nil, _nil); }

		size_type max_size(void) const { return _alloc.max_size(); }
		iter getNil(void) const { return _nil; }


	private:
		node*                   _root;
		node*                   _nil;
		size_type               _size;
		key_compare             _comp;
		allocator_type          _alloc;
		std::allocator<node>    _node_alloc;

		void _leftRotate(node *x) {
			node *y = x->right;
			x->right = y->left;
			if (y->left != _nil) { y->left->parent = x; }
			y->parent = x->parent;
			if (x->parent == nullptr) {
                _root = y;
            } else if (x == x->parent->left) {
                x->parent->left = y;
            } else {
                x->parent->right = y;
            }
			y->left = x;
			x->parent = y;
		}

		void _rightRotate(node *x) {
			node *y = x->left;
			x->left = y->right;
			if (y->right != _nil) { y->right->parent = x; }
			y->parent = x->parent;
			if (x->parent == nullptr) {
                _root = y;
            } else if (x == x->parent->right) {
                x->parent->right = y;
            } else {
                x->parent->left = y;
            }
			y->right = x;
			x->parent = y;
		}

		void _clearNode(node *n) {
			_alloc.deallocate(n->data, 1);
			_node_alloc.deallocate(n, 1);
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

		bool _hasChildren(node *n) const {
			if (n->left == _nil && n->right == _nil) { return false; }
			return true;
		}

		//replaces node x with node y
		void _nodeTransplant(node *x, node *y) {
			if (x->parent == nullptr) {
                _root = y;
            } else if (x == x->parent->left) {
                x->parent->left = y;
            } else {
                x->parent->right = y;
            }
			y->parent = x->parent;
		}

		//returns pointer to node with smallest key (left-most in the tree)
		node *_min(node *ptr) {
			while (ptr->left != _nil) { ptr = ptr->left; }
			return ptr;
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
				std::cout << (isLeft ? "?????????" : "?????????" );
				// print the value of the node
				std::cout << *n->data << std::endl;
				// enter the next tree level - left and right branch
				_printHelper(prefix + (isLeft ? "???   " : "    "), n->left, true);
				_printHelper(prefix + (isLeft ? "???   " : "    "), n->right, false);
			}
		}
	};
}

#endif
