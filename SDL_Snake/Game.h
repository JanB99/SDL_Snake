#pragma once
#include <iostream>
#include <vector>
#include <random>
#include "SDL.h"
#include "Texture.h"

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool isRunning;
} Game;

typedef struct { int x; int y; } Vec2;
typedef struct { Vec2 pos; Vec2 dir; } Body;

typedef struct {
	Vec2 head;
	std::vector<Body> tail;
	Vec2 dir;
	int length; 
} Snake;

typedef struct {
	SDL_Texture* appleTex;
	SDL_Texture* headTex;
	SDL_Texture* bodyTex;
	SDL_Texture* tailTex;
	SDL_Texture* grassTex;
	
} Textures;

const int FPS = 8, WIDTH = 800, HEIGHT = 800, RES = 50;

void init(const char* title, int width, int height, int flags, Game &game);
void render(SDL_Renderer* renderer, Snake snake, Vec2 apple, Textures gameTexs, TTF_Font* font);
void update(Snake& snake, Vec2& apple);
void handleEvents(Game& game, Snake& snake);
void clean(Game game);

Vec2 pickApplePos(Snake snake);