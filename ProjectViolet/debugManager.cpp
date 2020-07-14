//
//  debugManager.cpp
//  ProjectViolet
//
//  Created by Keegan Bilodeau on 7/14/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#include "debugManager.hpp"

#include <iostream>

DebugManager::DebugManager()
{
    
}

void DebugManager::startLoggingToFile()
{
    outputFile.open(__TIMESTAMP__, std::fstream::out | std::fstream::app);
    
    std::streambuf* tempbuf = outputFile.rdbuf();
    baseCoutBuffer = std::cout.rdbuf(tempbuf);
    
    std::cout << '[' <<  __TIMESTAMP__ << "]\n";
    
    tempbuf = nullptr;
}

void DebugManager::stopLoggingToFile()
{
    std::cout.rdbuf(baseCoutBuffer);
    
    outputFile.close();
}

void DebugManager::logMessage(std::string message, MessageSeverity severity)
{
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
            std::cout << "PROGRAM SHOULD BE TERMINATED!!\nIRRECOVERABLE ERROR: ";
            break;
    }
    
    std::cout << message << '\n';
}

void DebugManager::terminateApplication(Application &application, std::string terminatorName)
{
    
    ON_DEBUG(std::cout << terminatorName << " has called for the application to be terminated!\n";)
    
    application.stopNextIteration();
}

std::streambuf* DebugManager::baseCoutBuffer;
std::fstream DebugManager::outputFile;
