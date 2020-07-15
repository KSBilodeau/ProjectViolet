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
    void attachDebugger(Application &application)
    {
        mApplication = &application;
    }

    void detachDebugger()
    {
        mApplication = nullptr;
        mBaseCoutBuffer = nullptr;
    }

    void startLoggingToFile()
    {
        mOutputFile.open(__DATE__, std::fstream::out | std::fstream::app);
        
        std::streambuf* tempbuf = mOutputFile.rdbuf();
        mBaseCoutBuffer = std::cout.rdbuf(tempbuf);
        
        std::cout << '[' <<  __TIMESTAMP__ << "]\n";
        
        tempbuf = nullptr;
    }

    void stopLoggingToFile()
    {
        std::cout.rdbuf(mBaseCoutBuffer);
        
        mOutputFile.close();
    }

    void logMessage(std::string message, MessageSeverity severity)
    {
        assert(mApplication != nullptr && "IRRECOVERABLE ERROR: Application not attached to debugger!");
        
        switch (severity)
        {
            case Information:
                std::cout << "Information: ";
                break;
                
            case Warning:
                std::cout << "Warning: ";
                break;
                
            case SevereWarning:
                std::cout << "SEVERE WARNING: ";
                break;
                
            case Error:
                std::cout << "Error: ";
                break;
                
            case SevereError:
                std::cout << "SEVERE ERROR: ";
                break;
                
            case IrrecoverableError:
                std::cout << "TERMINATING PROGRAM!!\nIRRECOVERABLE ERROR: ";
                mApplication->stopNextIteration();
                break;
        }
        
        std::cout << message << '\n';
    }
}
