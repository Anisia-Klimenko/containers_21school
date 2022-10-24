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

    return 0;
}