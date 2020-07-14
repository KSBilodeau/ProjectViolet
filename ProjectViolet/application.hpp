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

#ifndef DEBUG
#define ON_DEBUG(x) do { } while (0);
#else
#define ON_DEBUG(x) do { x } while (0);
#endif

enum MessageSeverity
{
    Information,
    Warning,
    SevereWarning,
    Error,
    SevereError,
    IrrecoverableError
};

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
    void stopNextIteration();
    
    // Starts the application and runs the main loop
    bool initLibraries();
    
    // Loads the application's resources
    bool loadMedia();
    
    // Renders a single frame to the screen
    void renderFrame();
    
    // Updates the game by one iteration
    void update();
    
    // Contains the main game loop
    void mainLoop();
    
    // Utility function for logging information and errors to the console
    void logMessage(std::string message, MessageSeverity severity);
    
    static const int WINDOW_WIDTH = 750, WINDOW_HEIGHT = 750;
    
private:
    bool continueExecution;
    
    std::shared_ptr<SDL_Renderer> mRenderer;
    
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> mWindow;
};

#endif /* application_hpp */
