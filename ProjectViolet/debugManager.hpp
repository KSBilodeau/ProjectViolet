//
//  debugManager.hpp
//  ProjectViolet
//
//  Created by Keegan Bilodeau on 7/14/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#ifndef debugManager_hpp
#define debugManager_hpp

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>

#include "application.hpp"
#include "debugComponents.hpp"

class DebugManager
{
public:
    // Utility function that starts console output logging
    static void startLoggingToFile();
    
    // Utility function that ends console output logging
    static void stopLoggingToFile();
    
    // Utility function for logging messages to the console from outside the application class
    static void logMessage(std::string message, MessageSeverity severity);
    
    // Utility function for killing the application from outside the application class
    static void terminateApplication(Application &application, std::string terminatorName);
    
private:
    // Private to disable object instances of DebugManager
    DebugManager();
    
    // Stores the cout buffer before switching between file and console output mode
    static std::streambuf* baseCoutBuffer;
    
    // Stores the console output file
    static std::fstream outputFile;
};

#endif /* debugManager_hpp */
