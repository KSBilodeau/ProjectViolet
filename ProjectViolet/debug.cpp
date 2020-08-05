//
//  debug.cpp
//  ProjectViolet
//
//  Created by Keegan Bilodeau on 7/15/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#include "debug.hpp"

#include <iostream>

namespace Debug
{
    void startLoggingToFile()
    {
        // Create a file with the current date as the title for debug output logging
        mOutputFile.open(__DATE__, std::fstream::out | std::fstream::app);
        
        // Store the output files buffer in a temporary variable
        std::streambuf* tempbuf = mOutputFile.rdbuf();
        // Redirect cout buffer to the output file, and store the original in a variable
        mBaseCoutBuffer = std::cout.rdbuf(tempbuf);
        
        // Mark the start logging time in the file
        std::cout << '[' <<  __TIMESTAMP__ << "]\n";
        
        // Erase the contents of tempbuf to avoid wild pointers
        tempbuf = nullptr;
    }

    void stopLoggingToFile()
    {
        // Restore the original cout buffer
        std::cout.rdbuf(mBaseCoutBuffer);
        
        // Close the output file as it is no longer needed
        mOutputFile.close();
    }

    void logMessage(std::string message, MessageSeverity severity, int line, std::string fileName)
    {
        // Irrecoverable errors are the only error to interrupt the program, as it should only be used when
        // it is not safe to continue the program any longer
        switch (severity)
        {
            case Information:
                std::cerr << "Message ";
                break;
                
            case Warning:
                std::cerr << "Warning ";
                break;
                
            case SevereWarning:
                std::cerr << "SEVERE WARNING ";
                break;
                
            case Error:
                std::cerr << "Error ";
                break;
                
            case SevereError:
                std::cerr << "SEVERE ERROR ";
                break;
                
            case SDLError:
                std::cerr << "SDL Error ";
                break;
                
            case SDLImageError:
                std::cerr << "SDL_image Error ";
                break;
                
            case SDLFontError:
                std::cerr << "SDL_ttf Error ";
                break;
                
            case SDLMixerError:
                std::cerr << "SDL_mixer Error ";
                break;
                
            case IrrecoverableError:
                throw std::runtime_error("IRRECOVERABLE ERROR on line " + std::to_string(line) + " of " + fileName + ": " + message + '\n');
                break;
        }
        
        std::cerr << "on line " << line << " of " << fileName << ": " << message << '\n';
    }
}
