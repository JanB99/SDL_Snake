#include "Game.h"
#include "Texture.h"

int main(int argc, char* argv[]) {
	
	Game game{};
	init("Snake Game", WIDTH, HEIGHT, 0, game);

	TTF_Init();
	TTF_Font* comicSans = TTF_OpenFont("font/ComicSans.ttf", 64);
	if (!comicSans) {
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}

	Textures gameTexs = {
		loadTexture("assets/snake_apple.png", game.renderer),
		loadTexture("assets/snake_head.png", game.renderer),
		loadTexture("assets/snake_body.png", game.renderer),
		loadTexture("assets/snake_tail.png", game.renderer),
		loadTexture("assets/snake_grass.png", game.renderer)
	};

	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	std::srand(time(NULL));

	Snake snake = { {WIDTH / 2 / RES, HEIGHT / 2 / RES} };
	Vec2 apple = pickApplePos(snake);
	

	while (game.isRunning) {
		
		frameStart = SDL_GetTicks();

		handleEvents(game, snake);
		update(snake, apple);
		render(game.renderer, snake, apple, gameTexs, comicSans);

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	clean(game);

	return 0;
}