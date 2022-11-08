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
template <typename T>
void printValue(std::string TITLE, std::string key, T value) { std::cout << YELLOW << "[ " << TITLE << " ] " << GRN << key << END << " " << value << std::endl; }
template <typename T>
void printError(std::string key, T value) { std::cerr << RED << key << " : " << END << value << std::endl; }
#elif TERM
template <typename T>
void printValue(std::string key, T value) { std::cout << BLUE << key << " : " << END << value << std::endl; }
template <typename T>
void printValue(std::string TITLE, std::string key, T value) { std::cout << YELLOW << "[ " << TITLE << " ] " << BLUE << key << END << " " << value << std::endl; }
template <typename T>
void printError(std::string key, T value) { std::cerr << RED << key << " : " << END << value << std::endl; }
#else
template <typename T>
void printValue(std::string key, T value) { std::cout << key << " : " << value << std::endl; }
template <typename T>
void printValue(std::string TITLE, std::string key, T value) { std::cout << "[ " << TITLE << " ] " << key << " : " << value << std::endl; }
template <typename T>
void printError(std::string key, T value) { std::cerr << "[ ERROR ] : " << key << " : " << END << value << std::endl; }
#endif


int main(void) {
    int count = 0;

    ft::vector<int> vec1;
    printValue("EMPTY VECTOR", "size", vec1.size());

    ft::vector<char> vec2(5, 'a');
    printValue("VECTOR SIZE 5 VAL 'a'", "size", vec2.size());
    for (ft::vector<char>::const_iterator it = vec2.begin(); it != vec2.end(); it++) {
        printValue("elem " + std::to_string(count), *it);
        count++;
    }

    count = 0;
    ft::vector<char> vec3(vec2.begin(), vec2.end() - 1);
    printValue("VECTOR SIZE 4 VAL 'a' via iterator constructor", "size", vec3.size());
    for (ft::vector<char>::const_iterator it = vec3.begin(); it != vec3.end(); it++) {
        printValue("elem " + std::to_string(count), *it);
        count++;
    }

    count = 0;
    ft::vector<char> vec4(vec3);
    printValue("VECTOR SIZE 4 VAL 'a' as a copy of previous", "size", vec4.size());
    for (ft::vector<char>::const_iterator it = vec4.begin(); it != vec4.end(); it++) {
        printValue("elem " + std::to_string(count), *it);
        count++;
    }
//    ft::pair<std::string, std::string> a = ft::make_pair("el1", "el2");
//    printValue("first", a.first);
//    printValue("second", a.second);


    return 0;
}