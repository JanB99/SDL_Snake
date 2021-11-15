#include "Texture.h"

SDL_Texture* loadTexture(const char* fileName, SDL_Renderer* renderer) {
	SDL_Surface* tempSur = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSur);
	SDL_FreeSurface(tempSur);
	return tex;
}

SDL_Texture* loadTextureMessage(const char* message, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) {
	SDL_Surface* tempSur = TTF_RenderText_Solid(font, message, color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSur);
	SDL_FreeSurface(tempSur);
	return tex;
}