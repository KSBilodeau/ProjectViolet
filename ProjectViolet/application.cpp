//
//  application.cpp
//  ProjectViolet
//
//  Created by Keegan Bilodeau on 7/12/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#include <iostream>
#include <SDL_image.h>

#include "application.hpp"

Application::Application() : continueExecution(true), mRenderer(nullptr), mWindow(nullptr, SDL_DestroyWindow)
{
    
}

Application::~Application()
{
    free();
}

void Application::free()
{
    IMG_Quit();
    SDL_Quit();
}

bool Application::run()
{
    bool runSuccess = true;
        
    if (!initLibraries())
    {
        ON_DEBUG(logMessage("Failed to initialize application libraries!", MessageSeverity::IrrecoverableError);)
        runSuccess = false;
    }
    
    if (!loadMedia())
    {
        ON_DEBUG(logMessage("Failed to load application resources!", MessageSeverity::IrrecoverableError);)
        runSuccess = false;
    }
    
    // Used to poll SDL's event queue
    SDL_Event event;
    
    while (continueExecution)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                continueExecution = false;
        }
        
        SDL_SetRenderDrawColor(mRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mRenderer.get());
        
        SDL_RenderPresent(mRenderer.get());
        SDL_RenderClear(mRenderer.get());
    }
    
    return runSuccess;
}

void Application::stopNextIteration()
{
    // By setting the execution flag to false, the main loop will terminate
    // at the beginning of the next iteration
    continueExecution = false;
}

bool Application::initLibraries()
{
    bool success = true;
    
    // Initialize SDL with video and audio channels extensions enabled
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        ON_DEBUG(logMessage("Failed to initialize SDL!", MessageSeverity::SevereError);)
        ON_DEBUG(std::cout << "SDL Error: " << SDL_GetError() << '\n';)
        
        success = false;
    }
    else
    {
        mWindow = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(SDL_CreateWindow("Project Violet", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN), &SDL_DestroyWindow);
        
        if (mWindow == nullptr)
        {
            ON_DEBUG(logMessage("Failed to create the application's window!", MessageSeverity::SevereError);)
            ON_DEBUG(std::cout << "SDL Error: " << SDL_GetError() << '\n';)
            
            success = false;
        }
        else
        {
            mRenderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), &SDL_DestroyRenderer);
            
            if (mRenderer == nullptr)
            {
                ON_DEBUG(logMessage("Failed to create the application's renderer!", MessageSeverity::SevereError);)
                ON_DEBUG(std::cout << "SDL Error: " << SDL_GetError() << '\n';)
                
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(mRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
                
                // IMG flags have to be stored to check against IMG_INIT(...)
                int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
                
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    ON_DEBUG(logMessage("Failed to initialize SDL_image!", MessageSeverity::SevereError);)
                    ON_DEBUG(std::cout << "SDL_image Error: " << IMG_GetError() << '\n';)
                    
                    success = false;
                }
            }
        }
    }
    
    return success;
}

bool Application::loadMedia()
{
    bool success = true;
    
    return success;
}

void Application::logMessage(std::string message, MessageSeverity severity)
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
            std::cout << "TERMINATING PROGRAM!!\nIRRECOVERABLE ERROR: ";
            stopNextIteration();
            break;
    }
    
    std::cout << message << '\n';
}
