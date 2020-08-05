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
#include "debug.hpp"

using namespace Debug;

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
        
    // Catches any errors from application loading
    try
    {
        // Initializes SDL and its sub-libraries
        if (!initLibraries())
        {
            logMessage("Failed to initialize application libraries!", IrrecoverableError, __LINE__, __FILE_NAME__);
            runSuccess = false;
        }
        
        // Loads applications resources
        if (!loadMedia())
        {
            logMessage("Failed to load application resources!", IrrecoverableError, __LINE__, __FILE_NAME__);
            runSuccess = false;
        }
    }
    catch (std::runtime_error e)
    {
        // Output the error to the console
        std::cerr << e.what();
        
        stopApplication();
    }
    
    mainLoop();
    
    // Releases the library's resources
    free();
    
    return runSuccess;
}

void Application::stopApplication()
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
        ON_DEBUG(logMessage("Failed to initialize SDL!", SevereError, __LINE__, __FILE_NAME__);)
        ON_DEBUG(logMessage(SDL_GetError(), SDLError, __LINE__, __FILE_NAME__);)
        
        success = false;
    }
    else
    {
        // Create an SDL window unique pointer with custom deleter
        mWindow = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(SDL_CreateWindow("Project Violet", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN), &SDL_DestroyWindow);
        
        if (mWindow == nullptr)
        {
            ON_DEBUG(logMessage("Failed to create the application's window!", SevereError, __LINE__, __FILE_NAME__);)
            ON_DEBUG(logMessage(SDL_GetError(), SDLError, __LINE__, __FILE_NAME__);)
            
            success = false;
        }
        else
        {
            // Create an SDL Renderer shared pointer with custom deleter
            mRenderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), &SDL_DestroyRenderer);
            
            if (mRenderer == nullptr)
            {
                ON_DEBUG(logMessage("Failed to create the application's renderer!", SevereError, __LINE__, __FILE_NAME__);)
                ON_DEBUG(logMessage(SDL_GetError(), SDLError, __LINE__, __FILE_NAME__);)
                
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(mRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
                
                // IMG flags have to be stored to check against IMG_INIT(...)
                int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
                
                // Initialize SDL_image library with JPEG and PNG support
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    ON_DEBUG(logMessage("Failed to initialize SDL_image!", SevereError, __LINE__, __FILE_NAME__);)
                    ON_DEBUG(logMessage(IMG_GetError(), SDLImageError, __LINE__, __FILE_NAME__);)
                    
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

void Application::mainLoop()
{
    // Loops as long as the execution flag remains true
    while (continueExecution)
    {
        handleInput();
        
        update();

        renderFrame();
    }
}

void Application::handleInput()
{
    // Gets the most recent event in the SDL event queue
    while (SDL_PollEvent(&mEvent))
    {
        // If the user performs some form of QUIT operation, stop further application operation
        if (mEvent.type == SDL_QUIT)
            stopApplication();
    }
}

void Application::update()
{
    
}

void Application::renderFrame()
{
    SDL_SetRenderDrawColor(mRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(mRenderer.get());
    
    SDL_RenderPresent(mRenderer.get());
    SDL_RenderClear(mRenderer.get());
}
