#pragma once
#include "SDL.h"
#include "SDL_Image.h"
#include "SDL_ttf.h"

SDL_Texture* loadTexture(const char* fileName, SDL_Renderer* renderer);
SDL_Texture* loadTextureMessage(const char* message, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
