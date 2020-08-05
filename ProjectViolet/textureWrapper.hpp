//
//  textureWrapper.hpp
//  ProjectViolet
//
//  Created by Keegan Bilodeau on 7/27/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#ifndef textureWrapper_hpp
#define textureWrapper_hpp

#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

class TextureWrapper
{
public:
    // Initializes the wrapper's fields with default values
    TextureWrapper();
    
    // Calls for the attached texture to be freed
    ~TextureWrapper();
    
    // Creates a texture from a file and attaches it to the wrapper
    bool initFromFile(std::string filePath, double imageXScale, double imageYScale, std::shared_ptr<SDL_Renderer> &renderer, bool colorKeyImage = false, SDL_Color colorKey = {0xFF, 0x00, 0xDC});
    
    // Creates a texture from a string and attaches it to the wrapper
    bool initFromString(std::string text, std::shared_ptr<TTF_Font> &textFont, SDL_Color textColor, std::shared_ptr<SDL_Renderer> &renderer);
    
    // Creates a texture from a SDL rectangle and attaches it to the wrapper
    bool initFromRectangle(SDL_Rect baseRectangle, SDL_Color rectangleColor, std::shared_ptr<SDL_Renderer> &renderer);
    
    // Uses the SDL renderer to render the texture to the screen
    void render(int x, int y, bool fixed = false, SDL_Rect camera = {0, 0, 0, 0}, std::unique_ptr<SDL_Rect> clipRect = nullptr, double angle = 0.0f, std::unique_ptr<SDL_Point> center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    // Allows one to enable the alpha channel
    void setBlendMode(SDL_BlendMode blendMode);
    
    // Modifies the texture's color values based off the passed color
    void modifyTextureColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    
    // Changes the texture's scale factor
    void setTextureScale(double xScaleFactor, double yScaleFactor);
    
    // Returns the texture's orignal width (unscaled)
    int getUnscaledWidth();
    
    // Returns the texture's original height (unscaled)
    int getUnscaledHeight();
    
    // Returns the texture's scaled width
    int getScaledWidth();
    
    // Returns the texture's scaled height
    int getScaledHeight();
    
private:
    // Frees the attached texture to allow new textures to be attached
    void freeTexture();
    
    // Pointer to the renderer so that it doesn't have to be repeatedly passed to the texture
    std::shared_ptr<SDL_Renderer> mRenderer;
    
    // The SDL texure being wrapped
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> mWrappedTexture;
    
    // Texture's dimensions, has to be stored because they're lost when the SDL surface is converted to a texture
    int mWidth, mHeight;
    
    // Texture's x and y scale factor
    double mXScaleFactor, mYScaleFactor;
};

#endif /* textureWrapper_hpp */
