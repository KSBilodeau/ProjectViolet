//
//  application.hpp
//  ProjectViolet
//
//  Created by Keegan Bilodeau on 7/12/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#ifndef application_hpp
#define application_hpp

#include <memory>
#include <SDL.h>
#include <stdio.h>

class Application
{
public:
    // Initialize application variables
    Application();
    
    // Deconstruct application
    ~Application();
    
    // Frees the application's member variables
    void free();
    
    // Starts the application
    bool run();
    
    // Sets the application to stop at the end of its iteration
    void stopApplication();
    
    // Starts the application and runs the main loop
    bool initLibraries();
    
    // Loads the application's resources
    bool loadMedia();
    
    // Polls SDL for game input
    void handleInput();
    
    // Renders a single frame to the screen
    void renderFrame();
    
    // Updates the game by one iteration
    void update();
    
    // Contains the main game loop
    void mainLoop();
    
    static const int WINDOW_WIDTH = 750, WINDOW_HEIGHT = 750;
    
private:
    bool continueExecution;
    
    SDL_Event mEvent;
    
    std::shared_ptr<SDL_Renderer> mRenderer;
    
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> mWindow;
};

#endif /* application_hpp */
