#include "Texture.h"

SDL_Texture* loadTexture(const char* fileName, SDL_Renderer* renderer) {
	
	SDL_Surface* tempSur = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSur);
	SDL_FreeSurface(tempSur);
	return tex;
}