//
//  main.cpp
//  Song
//
//  Created by Xavier Chan on 2/27/16.
//  Copyright (c) 2016 Xavier Chan. All rights reserved.
//

#include <iostream>
#include "Song.h"

int main(int argc, const char * argv[])
{
    int melody[] = {1,1};
    int duration[] = {2,2};
    Song s(melody, duration);
    
    std::cout << s.getLength() << "\n";
    
    std::cout << s.getCurrentNote();
    
    std::cout << "Hello, World!\n";
    return 0;
}
