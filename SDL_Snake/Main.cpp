#include "Game.h"
#include "Texture.h"

int main(int argc, char* argv[]) {
	
	Game game{};
	init("Snake Game", WIDTH, HEIGHT, 0, game);

	Textures gameTexs = {
		loadTexture("assets/snake_apple.png", game.renderer),
		loadTexture("assets/snake_head.png", game.renderer),
		loadTexture("assets/snake_body.png", game.renderer),
		loadTexture("assets/snake_tail.png", game.renderer),
	};

	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	std::srand(time(NULL));

	int grid[WIDTH / RES][HEIGHT / RES];
	Snake snake = { {WIDTH / 2 / RES, HEIGHT / 2 / RES} };
	Vec2 apple = pickApplePos(snake);

	while (game.isRunning) {
		
		frameStart = SDL_GetTicks();

		handleEvents(game, snake);
		update(snake, apple);
		render(game.renderer, snake, apple, gameTexs);

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	clean(game);

	return 0;
}