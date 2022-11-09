//
// Created by Attack Cristina on 22.09.2022.
//

#ifdef STL
#include <vector>
namespace ft = std;
#else
#include "vector.h"
#endif

#include <iostream>
#include "main.h"

#if defined(TERM) && defined(STL)
template <typename T>
void printValue(std::string key, T value) { std::cout << GRN << key << " : " << END << value << std::endl; }
void printValue(std::string key, std::string value) { std::cout << GRN << key << " : " << END << value << std::endl; }
template <typename T>
void printValue(std::string TITLE, std::string key, T value) { std::cout << YELLOW << "[ " << TITLE << " ] " << GRN << key << END << " " << value << std::endl; }
template <typename T>
void printError(std::string key, T value) { std::cerr << RED << key << " : " << END << value << std::endl; }
#elif TERM
template <typename T>
void printValue(std::string key, T value) { std::cout << BLUE << key << " : " << END << value << std::endl; }
void printValue(std::string key, std::string value) { std::cout << BLUE << key << " : " << END << value << std::endl; }
template <typename T>
void printValue(std::string TITLE, std::string key, T value) { std::cout << YELLOW << "[ " << TITLE << " ] " << BLUE << key << END << " " << value << std::endl; }
template <typename T>
void printError(std::string key, T value) { std::cerr << RED << key << " : " << END << value << std::endl; }
#else
template <typename T>
void printValue(std::string key, T value) { std::cout << key << " : " << value << std::endl; }
void printValue(std::string key, std::string value) { std::cout << key << " : " << value << std::endl; }
template <typename T>
void printValue(std::string TITLE, std::string key, T value) { std::cout << "[ " << TITLE << " ] " << key << " : " << value << std::endl; }
template <typename T>
void printError(std::string key, T value) { std::cerr << "[ ERROR ] : " << key << " : " << END << value << std::endl; }
#endif


int main(void) {
//    int count = 0;
//
//    ft::vector<int> vec1;
//    printValue("EMPTY VECTOR vec1", "size", vec1.size());
//
//    ft::vector<char> vec2(5, 'a');
//    printValue("VECTOR SIZE 5 VAL 'a' vec2(5, 'a')", "size", vec2.size());
//    for (ft::vector<char>::const_iterator it = vec2.begin(); it != vec2.end(); it++) {
//        printValue("elem " + std::to_string(count), *it);
//        count++;
//    }
//
//    count = 0;
//    ft::vector<char> vec3(vec2.begin(), vec2.end() - 1);
//    printValue("VECTOR SIZE 4 VAL 'a' via iterator constructor vec3(vec2.begin(), vec2.end() - 1)", "size", vec3.size());
//    for (ft::vector<char>::const_iterator it = vec3.begin(); it != vec3.end(); it++) {
//        printValue("elem " + std::to_string(count), *it);
//        count++;
//    }
//
//    printValue("distance", ft::distance(vec2.begin(), vec2.end()));
//    count = 0;
//    ft::vector<char> vec4(vec3);
//    printValue("VECTOR SIZE 4 VAL 'a' vec4(vec3)", "size", vec4.size());
//    for (ft::vector<char>::const_iterator it = vec4.begin(); it != vec4.end(); it++) {
//        printValue("elem " + std::to_string(count), *it);
//        count++;
//    }

    ft::vector<std::string> vec;
    vec.push_back("frog");
    printValue("here", "main");
    vec.push_back("toad");
    vec.push_back("hamburger");
    vec.push_back("caffeine");
    vec.push_back("pizza");
    std::cout << "Creating vector, pushing some elements and\niterating with iterator" << std::endl;
    ft::vector<std::string>::iterator it = vec.begin();
    for (; it != vec.end(); it++)
        std::cout << " - " << *it << std::endl;
    std::cout << "Iterating again but this time with const iterator" << std::endl;
    ft::vector<std::string>::const_iterator cit = vec.begin();
    for (; cit != vec.end(); cit++)
        std::cout << " - " << *cit << std::endl;
    std::cout << "Comparing the two iterators (should be the same)" << std::endl;
    std::cout << " - it == cit: " << (it == cit) << std::endl;
    std::cout << " - it > cit: " << (it > cit) << std::endl;
    std::cout << " - it < cit: " << (it < cit) << std::endl;
    std::cout << " - it >= cit: " << (it >= cit) << std::endl;
    std::cout << " - it <= cit: " << (it <= cit) << std::endl;
    it = vec.begin();
    std::cout << "Comparing the two iterators (should be different)" << std::endl;
    std::cout << " - it == cit: " << (it == cit) << std::endl;
    std::cout << " - it > cit: " << (it > cit) << std::endl;
    std::cout << " - it < cit: " << (it < cit) << std::endl;
    std::cout << " - it >= cit: " << (it >= cit) << std::endl;
    std::cout << " - it <= cit: " << (it <= cit) << std::endl;
    std::cout << "Printing third element using begin + 2" << std::endl;
    std::cout << " - " << *(it + 2) << std::endl;
    std::cout << "Printing third element using operator[]" << std::endl;
    std::cout << " - " << it[2] << std::endl;
    std::cout << "Iterating with reverse_iterators" << std::endl;
    ft::vector<std::string>::reverse_iterator rit = vec.rbegin();
    for (; rit != vec.rend(); rit++)
        std::cout << " - " << *rit << std::endl;
    std::cout << "Comparing reverse iterator with const_reverse_iterator\n(should be different)" << std::endl;
    ft::vector<std::string>::const_reverse_iterator crit = vec.rbegin();
    std::cout << " - crit == rit: " << (crit == rit) << std::endl;
    std::cout << " - crit != rit: " << (crit != rit) << std::endl;
    std::cout << " - crit >= rit: " << (crit >= rit) << std::endl;
    std::cout << " - crit <= rit: " << (crit <= rit) << std::endl;
    std::cout << " - crit > rit: " << (crit > rit) << std::endl;
    std::cout << " - crit < rit: " << (crit < rit) << std::endl;
    std::cout << "Vector size" << std::endl;
    std::cout << " - " << vec.size() << std::endl;
    std::cout << "Vector capacity" << std::endl;
    std::cout << " - " << vec.capacity() << std::endl;
    std::cout << "Vector max_size" << std::endl;
    std::cout << " - " << vec.max_size() << std::endl;
    std::cout << "Vector after pushing 3 new objects" << std::endl;
    vec.push_back("duck");
    vec.push_back("capybara");
    vec.push_back("lizard");
    it = vec.begin();
    for (; it != vec.end(); it++)
        std::cout << " - " << *it << std::endl;
    std::cout << "Vector size" << std::endl;
    std::cout << " - " << vec.size() << std::endl;
    std::cout << "Vector capacity" << std::endl;
    std::cout << " - " << vec.capacity() << std::endl;
    std::cout << "Vector max_size" << std::endl;
    std::cout << " - " << vec.max_size() << std::endl;
    std::cout << "After pushing another object" << std::endl;
    vec.push_back("bruh");
    it = vec.begin();
    for (; it != vec.end(); it++)
        std::cout << " - " << *it << std::endl;
    std::cout << "Vector size" << std::endl;
    std::cout << " - " << vec.size() << std::endl;
    std::cout << "Vector capacity" << std::endl;
    std::cout << " - " << vec.capacity() << std::endl;
    std::cout << "Vector max_size" << std::endl;
    std::cout << " - " << vec.max_size() << std::endl;
    std::cout << "After popping the last object" << std::endl;
    vec.pop_back();
    it = vec.begin();
    for (; it != vec.end(); it++)
        std::cout << " - " << *it << std::endl;
    std::cout << "Vector size" << std::endl;
    std::cout << " - " << vec.size() << std::endl;
    std::cout << "Vector capacity" << std::endl;
    std::cout << " - " << vec.capacity() << std::endl;
    std::cout << "Vector max_size" << std::endl;
    std::cout << " - " << vec.max_size() << std::endl;
    std::cout << "After resizing to 8" << std::endl;
    vec.resize(8);
    it = vec.begin();
    for (; it != vec.end(); it++)
        std::cout << " - " << *it << std::endl;
    std::cout << "Vector size" << std::endl;
    std::cout << " - " << vec.size() << std::endl;
    std::cout << "Vector capacity" << std::endl;
    std::cout << " - " << vec.capacity() << std::endl;
    std::cout << "Vector max_size" << std::endl;
    std::cout << " - " << vec.max_size() << std::endl;
    std::cout << "After resizing to 32" << std::endl;
    vec.resize(32);
    it = vec.begin();
    for (; it != vec.end(); it++)
        std::cout << " - " << *it << std::endl;
    std::cout << "Vector size" << std::endl;
    std::cout << " - " << vec.size() << std::endl;
    std::cout << "Vector capacity" << std::endl;
    std::cout << " - " << vec.capacity() << std::endl;
    std::cout << "Vector max_size" << std::endl;
    std::cout << " - " << vec.max_size() << std::endl;
    ft::vector<std::string> v(8, "42");
    vec.assign(v.begin(), v.end());
    std::cout << "Vector after using assign to change contents" << std::endl;
    it = vec.begin();
    for (; it != vec.end(); it++)
        std::cout << " - " << *it << std::endl;
    std::cout << "Vector size" << std::endl;
    std::cout << " - " << vec.size() << std::endl;
    std::cout << "Vector capacity" << std::endl;
    std::cout << " - " << vec.capacity() << std::endl;
    std::cout << "Vector max_size" << std::endl;
    std::cout << " - " << vec.max_size() << std::endl;
    std::cout << "After resizing to 4" << std::endl;
    vec.resize(4);
    it = vec.begin();
    for (; it != vec.end(); it++)
        std::cout << " - " << *it << std::endl;
    std::cout << "Vector size" << std::endl;
    std::cout << " - " << vec.size() << std::endl;
    std::cout << "Vector capacity" << std::endl;
    std::cout << " - " << vec.capacity() << std::endl;
    std::cout << "Vector max_size" << std::endl;
    std::cout << " - " << vec.max_size() << std::endl;
    std::cout << "Changing first and last element of vector using operator[]" << std::endl;
    vec[0] = "frorg";
    vec[3] = "dogue";
    it = vec.begin();
    for (; it != vec.end(); it++)
        std::cout << " - " << *it << std::endl;
    std::cout << "Vector size" << std::endl;
    std::cout << " - " << vec.size() << std::endl;
    std::cout << "Vector capacity" << std::endl;
    std::cout << " - " << vec.capacity() << std::endl;
    std::cout << "Vector max_size" << std::endl;
    std::cout << " - " << vec.max_size() << std::endl;
    std::cout << "Return value of front()" << std::endl;
    std::cout << " - " << vec.front() << std::endl;
    std::cout << "Return value of back()" << std::endl;
    std::cout << " - " << vec.back() << std::endl;
    std::cout << "Capacity after using reserve(42)" << std::endl;
    vec.reserve(42);
    std::cout << " - " << vec.capacity() << std::endl;
    ft::vector<std::string> ve = vec;
    ve[0] = "toad";
    ve[2] = "borgor";
    std::cout << "New vector" << std::endl;
    it = ve.begin();
    for (; it != ve.end(); it++)
        std::cout << " - " << *it << std::endl;
    it = vec.begin();
    vec.swap(ve);
    std::cout << "New vector after swapping with old vector\niterated with old iterator to make sure its valid" << std::endl;
    for (; it != ve.end(); it++)
        std::cout << " - " << *it << std::endl << std::endl;


//    ft::pair<std::string, std::string> a = ft::make_pair("el1", "el2");
//    printValue("first", a.first);
//    printValue("second", a.second);


    return 0;
}