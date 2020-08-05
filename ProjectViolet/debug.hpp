//
//  debug.hpp
//  ProjectViolet
//
//  Created by Keegan Bilodeau on 7/15/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#ifndef debug_hpp
#define debug_hpp

#include <fstream>
#include <stdio.h>
#include <string>

#ifndef NDEBUG
#define ON_DEBUG(x) do { x } while (0);
#else
#define ON_DEBUG(x) do { } while (0);
#endif

enum MessageSeverity
{
    Information,
    Warning,
    SevereWarning,
    Error,
    SevereError,
    IrrecoverableError,
    SDLError,
    SDLImageError,
    SDLFontError,
    SDLMixerError
};

namespace
{
    // Stores the cout buffer before switching between file and console output mode
    std::streambuf* mBaseCoutBuffer = nullptr;
    
    // Stores the console output file
    std::fstream mOutputFile;
}

namespace Debug
{
    // Utility function that starts console output logging
    void startLoggingToFile();
    
    // Utility function that ends console output logging
    void stopLoggingToFile();
    
    // Utility function for logging messages to the console from outside the application class
    void logMessage(std::string message, MessageSeverity severity, int line, std::string fileName);
}

#endif /* debug_hpp */
