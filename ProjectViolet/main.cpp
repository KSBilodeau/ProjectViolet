//
//  main.cpp
//  ProjectViolet
//
//  Created by Keegan Bilodeau on 7/12/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#include <iostream>

#include "application.hpp"

int main(int argc, const char * argv[])
{
    Application application;
    
    if (application.run())
        return EXIT_SUCCESS;
    else
        return EXIT_FAILURE;
}
