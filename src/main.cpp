//
// Created by Attack Cristina on 22.09.2022.
//

#ifdef STL
#include <vector>
#include <stack>
namespace ft = std;
#else
#include "vector.h"
#include "stack.h"
#include "map.h"
#endif

#include <iostream>
#include <sstream>
#include <list>
#include <map>
#include "main.h"

#if defined(TERM) && defined(STL)
void printTitle(std::string TITLE, std::string key, T value) { std::cout << YELLOW << "[ " << TITLE << " ] " << END << std::endl; }
void printValue(std::string key, std::string value) { std::cout << GRN << key << " : " << END << value << std::endl; }
void printError(std::string key, std::string value) { std::cerr << RD << key << " : " << END << value << std::endl; }
#elif TERM
void printValue(std::string key, std::string value) { std::cout << BLUE << key << " : " << END << value << std::endl; }
void printTitle(std::string TITLE) { std::cout << YELLOW << "[ " << TITLE << " ] " << END << std::endl; }
void printError(std::string key, std::string value) { std::cerr << RD << key << " : " << END << value << std::endl; }
#else
void printValue(std::string key, std::string value) { std::cout << key << " : " << value << std::endl; }
void printTitle(std::string TITLE) { std::cout << "[ " << TITLE << " ] " << std::endl; }
void printError(std::string key, std::string value) { std::cerr << "[ ERROR ] : " << key << " : " << END << value << std::endl; }
#endif

template <typename T>
std::string vecToString(ft::vector<T> vec) {
    std::ostringstream out;
    typename ft::vector<T>::iterator it = vec.begin();
    for (; it != vec.end(); it++) { out << " - " << *it; }
    return out.str();
}

template <class T, class Container>
std::string stackToString(ft::stack<T,Container> st) {
    std::ostringstream out;
    ft::stack<T,Container> copy;
    copy = st;
    typename ft::stack<T,Container>::size_type size = st.size();
    typename ft::stack<T,Container>::size_type i = 0;
    for (; i < size; i++) {
        out << " - " << copy.top();
        copy.pop();
    }
    return out.str();
}

template <class Key, class Value>
std::string mapToString(ft::map<Key, Value> mp) {
    std::ostringstream out;
    typename ft::map<Key, Value>::iterator it = mp.begin();
    for(; it != mp.end(); it++) {
        out << " - { " << it->first << " : \"" << it->second << "\" }";
    }
    return out.str();
}

int main(void) {
//     testVector();
//     testStack();
    testMap();

//    ft::pair<std::string, std::string> a = ft::make_pair("el1", "el2");
//    printValue("first", a.first);
//    printValue("second", a.second);

    return 0;
}

void testMap() {
    printTitle("----------------------------------------------");
    printTitle("|                    MAP                     |");
    printTitle("----------------------------------------------");

    printTitle("creating empty map");
    ft::map<int, std::string> mp;

    ///////////////////////////////////////////////////////////////////////////////////////////

    printValue("is empty", std::to_string(mp.empty()));
    printTitle("putting elements using operator[] and operator=");
    mp[0] = "I";
    mp[1] = "like";
    mp[2] = "frogs";
    mp[3] = ".";

    printTitle("printing elements using iterators (from begin to end)");
    printValue("map", mapToString<int, std::string>(mp));

    printTitle("printing elements using iterators (from end to begin)");
    ft::map<int, std::string>::iterator it = mp.begin();
    it = --(mp.end());
    for (; it != mp.begin(); it--)
        std::cout << " - { " << it->first << " : \"" << it->second << "\" }";
    std::cout << std::endl;

    printTitle("printing elements using reverse iterators");
    ft::map<int, std::string>::reverse_iterator rit = mp.rbegin();
    for (; rit != mp.rend(); rit++)
        std::cout << " - { " << rit->first << " : \"" << rit->second << "\" }";
    std::cout << std::endl;

    ///////////////////////////////////////////////////////////////////////////////////////////

    printTitle("creating map via copy constructor");
    ft::map<int, std::string> mp2 = mp;
    printValue("map", mapToString<int, std::string>(mp2));
    printValue("size", std::to_string(mp2.size()));
    printValue("max_size", std::to_string(mp2.max_size()));

    printTitle("creating map from iterator range [begin() + 1, end()]");
    ft::map<int, std::string> mp3(++mp2.begin(), mp2.end());
    printValue("map", mapToString<int, std::string>(mp3));
    printValue("size", std::to_string(mp3.size()));
    printValue("max_size", std::to_string(mp3.max_size()));

    ///////////////////////////////////////////////////////////////////////////////////////////

    printValue("access 1 element using operator[]", mp[1]);
    printValue("access 1 element using at", mp.at(1));

    ///////////////////////////////////////////////////////////////////////////////////////////

    printTitle("erasing elements");
    printValue("before", mapToString<int, std::string>(mp));
    printValue("size", std::to_string(mp3.size()));
    printValue("is empty", std::to_string(mp.empty()));

    mp.erase(3);
    printValue("after erasing element 3", mapToString<int, std::string>(mp));
    printValue("size", std::to_string(mp.size()));
    printValue("is empty", std::to_string(mp.empty()));

    mp.erase(mp.begin());
    printValue("after erasing begin()", mapToString<int, std::string>(mp));
    printValue("size", std::to_string(mp.size()));
    printValue("is empty", std::to_string(mp.empty()));

    mp.erase(mp.begin(), mp.end());
    printValue("after erasing [begin(), end()]", mapToString<int, std::string>(mp));
    printValue("size", std::to_string(mp.size()));
    printValue("is empty", std::to_string(mp.empty()));

    ///////////////////////////////////////////////////////////////////////////////////////////

    printTitle("inserting elements");
    mp.insert(mp2.begin(), mp2.end());
    printValue("after inserting from iterator range", mapToString<int, std::string>(mp));
    printValue("size", std::to_string(mp.size()));
    printValue("is empty", std::to_string(mp.empty()));

    mp.insert(ft::make_pair(8, "borgor"));
    printValue("after inserting a pair", mapToString<int, std::string>(mp));
    printValue("size", std::to_string(mp.size()));
    printValue("is empty", std::to_string(mp.empty()));

    mp.insert(ft::make_pair(6, "duck"));
    printValue("after inserting one more pair", mapToString<int, std::string>(mp));
    printValue("size", std::to_string(mp.size()));
    printValue("is empty", std::to_string(mp.empty()));

    ///////////////////////////////////////////////////////////////////////////////////////////

    printValue("using find(6) to get element with key 6", mp.find(6)->second);
    printValue("using find(2) to get element with key 2", mp.find(2)->second);
    printValue("lower bound of key 3", mp.lower_bound(3)->second);
    printValue("upper bound of key 3", mp.upper_bound(3)->second);

    ///////////////////////////////////////////////////////////////////////////////////////////

    printTitle("erasing element with key 3, and then checking if begin() is still valid");
    it = mp.begin();
    mp.erase(3);
    printValue("begin() after erasing", it->second);

    ///////////////////////////////////////////////////////////////////////////////////////////

    printTitle("comparing iterator to begin (should be the same)");
    printValue("it == begin", std::to_string(it == mp.begin()));
    printValue("it != begin", std::to_string(it != mp.begin()));
    it++;
    printTitle("comparing changed iterator to begin (should be different)");
    printValue("it == begin", std::to_string(it == mp.begin()));
    printValue("it != begin", std::to_string(it != mp.begin()));

    ///////////////////////////////////////////////////////////////////////////////////////////

    printTitle("checking behavior of ft::make_pair");
    ft::pair<std::string, std::string> p = ft::make_pair("forg", "phroge");
    printValue("first", p.first);
    printValue("second", p.second);

    printTitle("trying to add element with existing key (6)");
    printValue("before", mapToString<int, std::string>(mp));
    printValue("size", std::to_string(mp.size()));
    mp.insert(ft::make_pair(6, "handborgor"));
    printValue("after", mapToString<int, std::string>(mp));
    printValue("size", std::to_string(mp.size()));

    ft::map<int, std::string> new_mp;
    printTitle("create map inserting pairs");
    new_mp.insert(ft::make_pair(1, "I"));
    new_mp.insert(ft::make_pair(2, "enjoy"));
    new_mp.insert(ft::make_pair(3, "containers"));
    new_mp.insert(ft::make_pair(4, "(not really)"));
    printValue("map", mapToString<int, std::string>(new_mp));
    printValue("size", std::to_string(new_mp.size()));

    printTitle("if key 3 is present");
    printValue("count(3)", std::to_string(new_mp.count(3)));

    ///////////////////////////////////////////////////////////////////////////////////////////

    printTitle("before swap (member function)");
    printValue("map 1", mapToString<int, std::string>(mp));
    printValue("map 2", mapToString<int, std::string>(new_mp));

    mp.swap(new_mp);
    printTitle("after swap");
    printValue("map 1", mapToString<int, std::string>(mp));
    printValue("map 2", mapToString<int, std::string>(new_mp));

    printTitle("before swap (non-member function)");
    printValue("map 1", mapToString<int, std::string>(mp));
    printValue("map 2", mapToString<int, std::string>(new_mp));

    ft::swap(mp, new_mp);
    printTitle("after swap");
    printValue("map 1", mapToString<int, std::string>(mp));
    printValue("map 2", mapToString<int, std::string>(new_mp));

    ///////////////////////////////////////////////////////////////////////////////////////////

    printTitle("check relational operators");
    printValue("map 1", mapToString<int, std::string>(mp));
    printValue("map 2", mapToString<int, std::string>(new_mp));
    printValue("map 1 == map 2", std::to_string(mp == new_mp));
    printValue("map 1 != map 2", std::to_string(mp != new_mp));
    printValue("map 1 > map 2 ", std::to_string(mp > new_mp));
    printValue("map 1 < map 2 ", std::to_string(mp < new_mp));
    printValue("map 1 >= map 2", std::to_string(mp >= new_mp));
    printValue("map 1 <= map 2", std::to_string(mp <= new_mp));

}

void testStack() {
    printTitle("----------------------------------------------");
    printTitle("|                   STACK                    |");
    printTitle("----------------------------------------------");

    #ifdef STL
    #define defContainer std::deque
    #else
    #define defContainer ft::vector
    #endif

    ft::stack<int> vst;
    printTitle("new empty default <int> stack");
    printValue("is empty", std::to_string(vst.empty()));
    printValue("size", std::to_string(vst.size()));

    ///////////////////////////////////////////////////////////////////////////////////////////

    vst.push(21);
    vst.push(123);
    vst.push(42);
    printTitle("after pushing some elements");
    printValue("stack", stackToString<int, defContainer<int> >(vst));
    printValue("top", std::to_string(vst.top()));
    printValue("is empty", std::to_string(vst.empty()));
    printValue("size", std::to_string(vst.size()));

    ///////////////////////////////////////////////////////////////////////////////////////////

    ft::stack<int> vstack;
    vstack = vst;
    printTitle("after using operator=");
    printValue("stack", stackToString<int, defContainer<int> >(vstack));
    printValue("top", std::to_string(vstack.top()));
    printValue("size", std::to_string(vstack.size()));

    ///////////////////////////////////////////////////////////////////////////////////////////

    vst.pop();
    printTitle("after popping an element");
    printValue("stack", stackToString<int, defContainer<int> >(vst));
    printValue("top", std::to_string(vst.top()));
    printValue("size", std::to_string(vst.size()));

    vst.pop();
    printTitle("after popping an element");
    printValue("stack", stackToString<int, defContainer<int> >(vst));
    printValue("top", std::to_string(vst.top()));
    printValue("size", std::to_string(vst.size()));

    vst.pop();
    printTitle("after popping an element");
    printValue("stack", stackToString<int, defContainer<int> >(vst));
    printValue("is empty", std::to_string(vst.empty()));
    printValue("size", std::to_string(vst.size()));

    ///////////////////////////////////////////////////////////////////////////////////////////

    vst.push(123);
    vst.push(42);
    printTitle("compare 2 stacks");
    printValue("stack 1", stackToString<int, defContainer<int> >(vst));
    printValue("stack 2", stackToString<int, defContainer<int> >(vstack));
    printValue("==", std::to_string(vst == vstack));
    printValue("!=", std::to_string(vst != vstack));
    printValue("> ", std::to_string(vst > vstack));
    printValue("< ", std::to_string(vst < vstack));
    printValue(">=", std::to_string(vst >= vstack));
    printValue("<=", std::to_string(vst <= vstack));

    ///////////////////////////////////////////////////////////////////////////////////////////

    ft::stack<int, std::list<int> > lst;
    printTitle("new empty std::list <int> stack");
    printValue("is empty", std::to_string(lst.empty()));
    printValue("size", std::to_string(lst.size()));

    lst.push(21);
    lst.push(123);
    lst.push(42);
    printTitle("after pushing some elements");
    printValue("stack", stackToString<int, std::list<int> >(lst));
    printValue("top", std::to_string(lst.top()));
    printValue("is empty", std::to_string(lst.empty()));
    printValue("size", std::to_string(lst.size()));

    lst.pop();
    printTitle("after popping an element");
    printValue("stack", stackToString<int, std::list<int> >(lst));
    printValue("top", std::to_string(lst.top()));
    printValue("size", std::to_string(lst.size()));

    lst.pop();
    printTitle("after popping an element");
    printValue("stack", stackToString<int, std::list<int> >(lst));
    printValue("top", std::to_string(lst.top()));
    printValue("size", std::to_string(lst.size()));

    lst.pop();
    printTitle("after popping an element");
    printValue("stack", stackToString<int, std::list<int> >(lst));
    printValue("is empty", std::to_string(lst.empty()));
    printValue("size", std::to_string(lst.size()));

}

void testVector() {
    printTitle("----------------------------------------------");
    printTitle("|                   VECTOR                   |");
    printTitle("----------------------------------------------");

    ft::vector<std::string> vec;
    printTitle("creating empty vector");
    printValue("is empty?", std::to_string(vec.empty()));
    vec.push_back("frog");
    vec.push_back("toad");
    vec.push_back("hamburger");
    vec.push_back("caffeine");
    vec.push_back("pizza");
    printTitle("pushing some elements and iterating with iterator");
    ft::vector<std::string>::iterator it = vec.begin();
    for (; it != vec.end(); it++) {
        std::cout << " - " << *it;
    }
    std::cout << std::endl;

    printTitle("iterating with const iterator");
    ft::vector<std::string>::const_iterator cit = vec.begin();
    for (; cit != vec.end(); cit++) {
        std::cout << " - " << *cit;
    }
    std::cout << std::endl;

    printTitle("iterating with reverse_iterators");
    ft::vector<std::string>::reverse_iterator rit = vec.rbegin();
    for (; rit != vec.rend(); rit++) {
        std::cout << " - " << *rit;
    }
    std::cout << std::endl;

    ///////////////////////////////////////////////////////////////////////////////////////////

    printTitle("comparing the two iterators (should be the same)");
    printValue("it == cit", std::to_string(it == cit));
    printValue("it > cit ", std::to_string(it > cit));
    printValue("it < cit ", std::to_string(it < cit));
    printValue("it >= cit", std::to_string(it >= cit));
    printValue("it <= cit", std::to_string(it <= cit));

    printTitle("comparing reverse iterator with const_reverse_iterator (should be different)");
    ft::vector<std::string>::const_reverse_iterator crit = vec.rbegin();
    printValue("rit == crit", std::to_string(rit == crit));
    printValue("rit > crit ", std::to_string(rit > crit));
    printValue("rit < crit ", std::to_string(rit < crit));
    printValue("rit >= crit", std::to_string(rit >= crit));
    printValue("rit <= crit", std::to_string(rit <= crit));

    ///////////////////////////////////////////////////////////////////////////////////////////

    it = vec.begin();
    printTitle("access elements");
    printValue("third element using *(begin + 2)", *(it + 2));
    printValue("third element using operator[]", it[2]);
    printValue("return value of front()", vec.front());
    printValue("return value of back()", vec.back());

    ///////////////////////////////////////////////////////////////////////////////////////////

    printTitle("size, capacity, max_size");
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    printTitle("vector after pushing 3 new objects");
    vec.push_back("duck");
    vec.push_back("capybara");
    vec.push_back("lizard");
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    printTitle("after pushing another object");
    vec.push_back("bruh");
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    printTitle("after popping the last object");
    vec.pop_back();
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    printTitle("after resizing to 8");
    vec.resize(8);
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    printTitle("after resizing to 32");
    vec.resize(32);
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    ft::vector<std::string> v(8, "42");
    vec.assign(v.begin(), v.end());
    printTitle("after using assign to change contents");
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    vec.insert(vec.end() - 2, "24");
    printTitle("after using insert(vec.end() - 2, \"24\") to change contents");
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    vec.erase(vec.begin(), vec.begin() + 3);
    printTitle("after using erase(vec.begin(), vec.begin() + 3) to change contents");
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    printTitle("after resizing to 4");
    vec.resize(4);
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    printTitle("changing first and last element of vector using operator[]");
    vec[0] = "frorg";
    vec[3] = "dogue";
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    printTitle("changing second of vector using at()");
    vec.at(1) = "21";
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    vec.reserve(42);
    printTitle("after using reserve(42)");
    printValue("vector", vecToString<std::string>(vec));
    printValue("vector size", std::to_string(vec.size()));
    printValue("vector capacity", std::to_string(vec.capacity()));
    printValue("vector max_size", std::to_string(vec.max_size()));

    ft::vector<std::string> ve;
    ve = vec;
    printTitle("after using operator=");
    printValue("vector", vecToString<std::string>(ve));
    printValue("vector size", std::to_string(ve.size()));
    printValue("vector capacity", std::to_string(ve.capacity()));
    printValue("vector max_size", std::to_string(ve.max_size()));

    ///////////////////////////////////////////////////////////////////////////////////////////

    ve.pop_back();
    printTitle("before swap (member function)");
    printValue("vector 1", vecToString<std::string>(ve));
    printValue("vector 2", vecToString<std::string>(vec));
    it = vec.begin();
    vec.swap(ve);
    printTitle("after swapping iterated with old iterator to make sure its valid");
    printValue("vector 1", vecToString<std::string>(ve));
    printValue("vector 2", vecToString<std::string>(vec));

    printTitle("before swap (non-member function)");
    printValue("vector 1", vecToString<std::string>(ve));
    printValue("vector 2", vecToString<std::string>(vec));
    it = vec.begin();
    ft::swap(ve, vec);
    printTitle("after swapping iterated with old iterator to make sure its valid");
    printValue("vector 1", vecToString<std::string>(ve));
    printValue("vector 2", vecToString<std::string>(vec));

    ///////////////////////////////////////////////////////////////////////////////////////////

    ft::vector<std::string> vect(vec.begin() + 1, vec.end() - 1);
    printTitle("creating vector with iterators constructor (begin() + 1, end() - 1)");
    printValue("vector", vecToString<std::string>(vect));

    printTitle("creating vector with a copy constructor");
    ft::vector<std::string> vector(vect);
    printValue("vector", vecToString<std::string>(vector));

    ///////////////////////////////////////////////////////////////////////////////////////////

    vec.at(2) = "41";
    printTitle("compare 2 vectors");
    printValue("vector 1", vecToString<std::string>(ve));
    printValue("vector 2", vecToString<std::string>(vec));
    printValue("==", std::to_string(ve == vec));
    printValue("!=", std::to_string(ve != vec));
    printValue("> ", std::to_string(ve > vec));
    printValue("< ", std::to_string(ve < vec));
    printValue(">=", std::to_string(ve >= vec));
    printValue("<=", std::to_string(ve <= vec));

}
