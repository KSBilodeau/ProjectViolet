//
//  textureWrapper.cpp
//  ProjectViolet
//
//  Created by Keegan Bilodeau on 7/27/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#include "debug.hpp"
#include "textureWrapper.hpp"

#include <SDL_image.h>

TextureWrapper::TextureWrapper() : mRenderer(nullptr), mWrappedTexture(nullptr, nullptr), mWidth(0), mHeight(0), mXScaleFactor(0.0f), mYScaleFactor(0.0f)
{
    
}

TextureWrapper::~TextureWrapper()
{
    freeTexture();
}

void TextureWrapper::freeTexture()
{
    mRenderer = nullptr;
    mWrappedTexture = nullptr;
    
    mWidth = 0;
    mHeight = 0;
    
    mXScaleFactor = 0.0f;
    mYScaleFactor = 0.0f;
}

bool TextureWrapper::initFromFile(std::string filePath, double imageXScale, double imageYScale, std::shared_ptr<SDL_Renderer> &renderer, bool colorKeyImage, SDL_Color colorKey)
{
    // Loading success flag
    bool success = false;
    
    // Releases any attached textures
    if (mWrappedTexture != nullptr)
        freeTexture();
    
    // Pass the application's renderer to the texture
    mRenderer = renderer;
    
    // Loads the image as a SDL surface
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> loadedSurface(IMG_Load(filePath.c_str()), &SDL_FreeSurface);
    
    // Check if it loads successfully
    if (!loadedSurface)
    {
        ON_DEBUG(Debug::logMessage("Failed to load image from " + filePath + "!", SevereError, __LINE__, __FILE_NAME__);)
        ON_DEBUG(Debug::logMessage(IMG_GetError(), SDLImageError, __LINE__, __FILE_NAME__);)
        
        success = false;
    }
    else
    {
        // Color keys the image if enabled
        if (colorKeyImage)
            SDL_SetColorKey(loadedSurface.get(), SDL_TRUE, SDL_MapRGB(loadedSurface->format, colorKey.r, colorKey.g, colorKey.b));
        
        // Attaches the 
        mWrappedTexture = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>(SDL_CreateTextureFromSurface(mRenderer.get(), loadedSurface.get()), &SDL_DestroyTexture);
        
        // Check if its loaded successfully
        if (!mWrappedTexture)
        {
            ON_DEBUG(Debug::logMessage("Failed to convert " + filePath + " into a texture!", SevereError, __LINE__, __FILE_NAME__);)
            ON_DEBUG(Debug::logMessage(SDL_GetError(), SDLError, __LINE__, __FILE_NAME__);)
            
            success = false;
        }
        else
        {
            // Preserve the texture's dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
            
            // Store the texture scale resizing the render quad in TextureWrapper::render(...)
            mXScaleFactor = imageXScale;
            mYScaleFactor = imageYScale;
        }
    }
    
    return success;
}

bool TextureWrapper::initFromString(std::string text, std::shared_ptr<TTF_Font> &textFont, SDL_Color textColor, std::shared_ptr<SDL_Renderer> &renderer)
{
    // Loading success flag
    bool success = true;
    
    // Release any texture previously attached to the wrapper
    if (!mWrappedTexture)
        freeTexture();
    
    // Attach the renderer to the texture
    mRenderer = renderer;
    
    // Create a surface containing text using TTF
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> loadedSurface(TTF_RenderText_Blended_Wrapped(textFont.get(), text.c_str(), textColor, 300 * 1.776), &SDL_FreeSurface);
    
    // Check if it was loaded successfully
    if (!loadedSurface)
    {
        ON_DEBUG(Debug::logMessage("Unable to render text to a surface!", SevereError, __LINE__, __FILE_NAME__);)
        ON_DEBUG(Debug::logMessage(TTF_GetError(), SDLFontError, __LINE__, __FILE_NAME__);)
        
        success = false;
    }
    else
    {
        // Convert the surface to a texture
        mWrappedTexture = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>(SDL_CreateTextureFromSurface(mRenderer.get(), loadedSurface.get()), &SDL_DestroyTexture);
        
        // Check if the conversion was successful
        if (!mWrappedTexture)
        {
            ON_DEBUG(Debug::logMessage("Unable to convert the rendered text to a texture!", SevereError, __LINE__, __FILE_NAME__);)
            ON_DEBUG(Debug::logMessage(SDL_GetError(), SDLError, __LINE__, __FILE_NAME__);)
            
            success = false;
        }
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
            
            mXScaleFactor = 1;
            mYScaleFactor = 1;
        }
    }
    
    return success;
}

bool TextureWrapper::initFromRectangle(SDL_Rect baseRectangle, SDL_Color rectangleColor, std::shared_ptr<SDL_Renderer> &renderer)
{
    // Loading success flag
    bool success = true;
    
    // Release any previously attached textures
    if (!mWrappedTexture)
        freeTexture();
    
    // Attach the renderer to the texture
    mRenderer = renderer;
    
    // Create a targetable texture
    mWrappedTexture = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>(SDL_CreateTexture(mRenderer.get(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, baseRectangle.w, baseRectangle.h), &SDL_DestroyTexture);
    
    // Check if it was created successfully
    if (!mWrappedTexture)
    {
        ON_DEBUG(Debug::logMessage("Failed to create a targetable texture!", SevereError, __LINE__, __FILE_NAME__);)
        ON_DEBUG(Debug::logMessage(SDL_GetError(), SDLError, __LINE__, __FILE_NAME__);)
        
        success = false;
    }
    else
    {
        // Set the dimensions
        mWidth = baseRectangle.w;
        mHeight = baseRectangle.h;
        
        // Set the scale
        mXScaleFactor = 1;
        mYScaleFactor = 1;
        
        // Make the texture the color of the rectangle:
        // 1) Target the texture
        SDL_SetRenderTarget(mRenderer.get(), mWrappedTexture.get());
        // 2) Set the render draw color to the color of the rectanlge
        SDL_SetRenderDrawColor(mRenderer.get(), rectangleColor.r, rectangleColor.g, rectangleColor.b, rectangleColor.a);
        // 3) Paint the screen by "clearing" it
        SDL_RenderClear(mRenderer.get());
        // 4) Reset the draw color
        SDL_SetRenderDrawColor(mRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
        // 5) Reset the texture target
        SDL_SetRenderTarget(mRenderer.get(), nullptr);
    }
    
    return success;
}

void TextureWrapper::render(int x, int y, bool fixed, SDL_Rect camera, std::unique_ptr<SDL_Rect> clipRect, double angle, std::unique_ptr<SDL_Point> center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad {x, y, mWidth, mHeight};
    
    // Adjust the texture based off a camera variable if true
    if (!fixed)
    {
        renderQuad.x -= camera.x;
        renderQuad.y -= camera.y;
    }
    
    // Applies the clip dimensions if a clip rectangle is passed
    if (clipRect)
    {
        renderQuad.w = clipRect->w;
        renderQuad.h = clipRect->h;
    }
    
    renderQuad.x *= mXScaleFactor;
    renderQuad.y *= mYScaleFactor;
    
    SDL_RenderCopyEx(mRenderer.get(), mWrappedTexture.get(), clipRect.get(), &renderQuad, angle, center.get(), flip);
}

void TextureWrapper::setBlendMode(SDL_BlendMode blendMode)
{
    SDL_SetTextureBlendMode(mWrappedTexture.get(), blendMode);
}

void TextureWrapper::modifyTextureColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetTextureColorMod(mWrappedTexture.get(), r, g, b);
    SDL_SetTextureAlphaMod(mWrappedTexture.get(), a);
}

void TextureWrapper::setTextureScale(double xScaleFactor, double yScaleFactor)
{
    mXScaleFactor = xScaleFactor;
    mYScaleFactor = yScaleFactor;
}

int TextureWrapper::getUnscaledWidth()
{
    return mWidth;
}

int TextureWrapper::getUnscaledHeight()
{
    return mHeight;
}

int TextureWrapper::getScaledWidth()
{
    return mWidth * mXScaleFactor;
}

int TextureWrapper::getScaledHeight()
{
    return mHeight * mYScaleFactor;
}
