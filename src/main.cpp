//
// Created by Attack Cristina on 22.09.2022.
//

#include <iostream>
#include "vector.h"
#include "main.h"

void printValue(std::string key, std::string value) {
    std::cout << BLUE << key << " : " << END << value << std::endl;
}

void printError(std::string key, std::string value) {
    std::cerr << RED << key << " : " << END << value << std::endl;
}

int main(void) {
#ifdef STL
    std::cout << "STL" << std::endl;
#else
    std::cout << "NO STL" << std::endl;
#endif
    return 0;
}