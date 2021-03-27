//
//  main.cpp
//  Template-DynamicArray
//
//  Created by ChrisLam on 26/03/2021.
//

#include <iostream>
#include "DynamicArray.hpp"

int main(int argc, const char * argv[]) {
    DynamicArray arr;
    
    for (int i = 0; i < 20; i += 2) {
        arr.append(i);
    }
    
    for (int i = 0; i < 20; i += 2) {
        arr.append(i);
    }
    
    std::cout << arr;
    return 0;
}
