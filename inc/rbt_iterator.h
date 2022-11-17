//
// Created by Anisia Klimenko on 17.11.2022.
//

#ifndef RBT_ITERATOR_H
#define RBT_ITERATOR_H

#include "utility.h"

namespace ft {
    template <typename T, class Tree>
    class const_RBT_Iterator;

    template <typename T, class Tree>
    class RBT_Iterator : ft::iterator<ft::bidirectional_iterator_tag, T> {
    public:

        typedef typename Tree::value_type                                                               value_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category    iterator_category;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type      difference_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer              pointer;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference            reference;

        RBT_Iterator(T *ptr = nullptr) : _ptr(ptr), _nil(ptr) {
            if (ptr) {
                while (_nil->left) {
                    _nil = _nil->left;
                }
            }
        }

        RBT_Iterator(T *ptr,T *nil) : _ptr(ptr), _nil(nil) {}
        RBT_Iterator(const RBT_Iterator &copy) : _ptr(copy._ptr), _nil(copy._nil) {}
        virtual ~RBT_Iterator(void) {}

        RBT_Iterator &operator=(const RBT_Iterator &copy) {
            _ptr = copy._ptr;
            _nil = copy._nil;
            _prev = copy._prev;
            return *this;
        }

        T *base() const { return _ptr; }

        reference operator*() const { return *(_ptr->data); }
        pointer operator->(void) const { return &(operator*()); }

        RBT_Iterator &operator++(void) {
            T *temp = _ptr;
            if (temp == nullptr) {
                temp = _prev;
            } else if (temp->right != _nil) {
                temp = temp->right;
                while (temp->left != _nil) { temp = temp->left; }
            } else if (temp->parent && temp == temp->parent->left) {
                temp = temp->parent;
            } else if (temp->parent && temp == temp->parent->right) {
                while (temp->parent && temp == temp->parent->right)
                    temp = temp->parent;
                temp->parent != nullptr ? temp = temp->parent : temp = _nil;
            } else {
                temp = _nil;
            }
            _prev = _ptr;
            _ptr = temp;
            return *this;
        }

        RBT_Iterator operator++(int) {
            RBT_Iterator temp = *this;
            ++(*this);
            return (temp);
        }

        RBT_Iterator &operator--(void) {
            T *temp = _ptr;
            if (!temp->parent && temp->left == _nil) {
                temp = temp->parent;
            } else if (temp == _nil) {
                temp = _nil->parent;
            } else if (temp->left != _nil && temp->left) {
                temp = temp->left;
                while (temp->right != _nil) {
                    temp = temp->right;
                }
            } else if (temp->parent && temp == temp->parent->right) {
                temp = temp->parent;
            } else if (temp->parent && temp == temp->parent->left) {
                while (temp->parent && temp == temp->parent->left)
                    temp = temp->parent;
                temp->parent ? temp = temp->parent : temp = nullptr;
            } else {
                temp = _nil->parent;
            }
            _prev = _ptr;
            _ptr = temp;
            return *this;
        }

        RBT_Iterator operator--(int) {
            RBT_Iterator temp = *this;
            --(*this);
            return (temp);
        }

        T *getNil(void) const { return _nil; }
        T *getPrev(void) const { return _prev; }

        bool operator==(const const_RBT_Iterator<T, Tree> &rhs) const { return (this->base() == rhs.base()); }
        bool operator==(const RBT_Iterator<T, Tree> &rhs) const { return (this->base() == rhs.base()); }
        bool operator!=(const const_RBT_Iterator<T, Tree> &rhs) const { return (this->base() != rhs.base()); }
        bool operator!=(const RBT_Iterator<T, Tree> &rhs) const { return (this->base() != rhs.base()); }

    private:
        T *_ptr;
        T *_nil;
        T *_prev;
    };

    template <typename T, class Tree>
    class const_RBT_Iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
    {
    public:

        typedef const typename Tree::value_type value_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type difference_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer pointer;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

        const_RBT_Iterator(T *nil = nullptr) : _ptr(), _nil(nil) {}
        const_RBT_Iterator(T *ptr,T *nil) : _ptr(ptr), _nil(nil) {}
        const_RBT_Iterator(const const_RBT_Iterator &copy) : _ptr(copy._ptr), _nil(copy._nil) {}
        const_RBT_Iterator(const RBT_Iterator<T, Tree> &copy) { *this = copy; }
        virtual ~const_RBT_Iterator(void) {}

        const_RBT_Iterator &operator=(const const_RBT_Iterator &copy) {
            _ptr = copy._ptr;
            _nil = copy._nil;
            _prev = copy._prev;
            return (*this);
        }

        const_RBT_Iterator &operator=(const RBT_Iterator<T, Tree> &copy) {
            _ptr = copy.base();
            _nil = copy.getNil();
            _prev = copy.getPrev();
            return (*this);
        }

        T *base(void) const { return _ptr; }
        const reference operator*(void) const { return *(_ptr->data)}
        const pointer operator->(void) const { return (&(this->operator*())); }

        //not sure what to do when iterator reaches the end
        const_RBT_Iterator &operator++(void) {
            T *temp = _ptr;
            if (temp == nullptr) {
                temp = _prev;
            } else if (temp->right != _nil) {
                temp = temp->right;
                while (temp->left != _nil)
                    temp = temp->left;
            } else if (temp->parent && temp == temp->parent->left) {
                temp = temp->parent;
            } else if (temp->parent && temp == temp->parent->right) {
                while (temp->parent && temp == temp->parent->right)
                    temp = temp->parent;
                temp->parent ? temp = temp->parent : temp = _nil;
            } else {
                temp = _nil;
            }
            _prev = _ptr;
            _ptr = temp;
            return *this;
        }

        const_RBT_Iterator operator++(int) {
            const_RBT_Iterator temp = *this;
            ++(*this);
            return (temp);
        }

        const_RBT_Iterator &operator--(void) {
            T *temp = _ptr;
            if (temp == _nil) {
                temp = _nil->parent;
            } else if (temp->left != _nil) {
                temp = temp->left;
                while (temp->right != _nil)
                    temp = temp->right;
            } else if (temp->parent && temp == temp->parent->right) {
                temp = temp->parent;
            } else if (temp->parent && temp == temp->parent->left) {
                while (temp->parent && temp == temp->parent->left)
                    temp = temp->parent;
                temp->parent ? temp = temp->parent : temp = nullptr;
            }
            _prev = _ptr;
            _ptr = temp;
            return *this;
        }

        const_RBT_Iterator operator--(int) {
            const_RBT_Iterator temp = *this;
            --(*this);
            return (temp);
        }

        bool operator==(const const_RBT_Iterator<T, Tree> &rhs) const { return (this->base() == rhs.base()); }
        bool operator==(const RBT_Iterator<T, Tree> &rhs) const { return (this->base() == rhs.base()); }
        bool operator!=(const const_RBT_Iterator<T, Tree> &rhs) const { return (this->base() != rhs.base()); }
        bool operator!=(const RBT_Iterator<T, Tree> &rhs) const { return (this->base() != rhs.base()); }

    private:
        T *_ptr;
        T *_nil;
        T *_prev;
    };
}

#endif //RBT_ITERATOR_H
