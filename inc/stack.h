//
// Created by Attack Cristina on 11/14/22.
//

#ifndef STACK_H
#define STACK_H

#include "vector.h"
#include "main.h"

namespace ft {
    template <class T, class Container = ft::vector<T> >
    class stack {
    public:
        typedef             T                           value_type;
        typedef             Container                   container_type;
        typedef typename    container_type::size_type   size_type;

        // constructor
        explicit stack (const container_type& ctnr = container_type()) : _c(ctnr) {};
        // destructor
        ~stack() {};

        // https://en.cppreference.com/w/cpp/container/stack/operator%3D
        stack& operator=( const stack& other ) {
            _c = other._c;
            return *this;
        };

        // https://cplusplus.com/reference/stack/stack/top/
        value_type& top() { return _c.back(); };
        const value_type& top() const { return _c.back(); };

        // https://cplusplus.com/reference/stack/stack/empty/
        bool empty() const { return _c.empty(); };

        // https://cplusplus.com/reference/stack/stack/size/
        size_type size() const { return _c.size(); };

        // https://cplusplus.com/reference/stack/stack/push/
        void push (const value_type& val) { _c.push_back(val); };

        // https://cplusplus.com/reference/stack/stack/pop/
        void pop() { _c.pop_back(); };

        template <class T, class Container>
        friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
        template <class T, class Container>
        bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
        template <class T, class Container>
        friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
        template <class T, class Container>
        friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
        template <class T, class Container>
        friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
        template <class T, class Container>
        friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

    protected:
        container_type _c;
    };

    template <class T, class Container>
    bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs._c == rhs._c); }
    template <class T, class Container>
    bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs._c != rhs._c); }
    template <class T, class Container>
    bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs._c < rhs._c); }
    template <class T, class Container>
    bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs._c <= rhs._c); }
    template <class T, class Container>
    bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs._c > rhs._c); }
    template <class T, class Container>
    bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs._c >= rhs._c); }

}

#endif //STACK_H
