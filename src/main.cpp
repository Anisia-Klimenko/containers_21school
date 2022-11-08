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
void printValue(std::string key, std::string value) { std::cout << GRN << key << " : " << END << value << std::endl; }
void printError(std::string key, std::string value) { std::cerr << RED << key << " : " << END << value << std::endl; }
#elif TERM
void printValue(std::string key, std::string value) { std::cout << BLUE << key << " : " << END << value << std::endl; }
void printError(std::string key, std::string value) { std::cerr << RED << key << " : " << END << value << std::endl; }
#else
void printValue(std::string key, std::string value) { std::cout << key << " : " << value << std::endl; }
void printError(std::string key, std::string value) { std::cerr << "[ ERROR ] : " << key << " : " << END << value << std::endl; }
#endif


int main(void) {
    ft::pair<std::string, std::string> a = ft::make_pair("el1", "el2");
    printValue("first", a.first);
    printValue("second", a.second);
    return 0;
}