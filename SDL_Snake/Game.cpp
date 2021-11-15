#include "Game.h"
#include "Math.h"

void init(const char* title, int width, int height, int flags, Game& game) {
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		std::cout << "subsystems init error" << std::endl;
	}
	game.window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	game.renderer = SDL_CreateRenderer(game.window, -1, 0);
	game.isRunning = true;
}

void render(SDL_Renderer* renderer, Snake snake, Vec2 apple, Textures gameTexs) {
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderClear(renderer);

	SDL_Rect r;

	// grid
	for (int x = 0; x < WIDTH / RES; x++) {
		for (int y = 0; y < HEIGHT / RES; y++) {
			r = { x * RES, y * RES, RES, RES };
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderDrawRect(renderer, &r);
		}
	}

	//apple
	r = { apple.x * RES, apple.y * RES, RES, RES };
	SDL_RenderCopy(renderer, gameTexs.appleTex, NULL, &r);

	//head
	r = { snake.head.x * RES, snake.head.y * RES, RES, RES };
	double angle = atan2(snake.dir.y, snake.dir.x) * (180/M_PI) + 90;
	SDL_RenderCopyEx(renderer, gameTexs.headTex, NULL, &r, angle, NULL, SDL_FLIP_NONE);

	//tail
	for (int i = 1; i < snake.tail.size(); i++) {
		r = { snake.tail[i].pos.x * RES, snake.tail[i].pos.y * RES, RES, RES };
		angle = atan2(snake.tail[i].dir.y, snake.tail[i].dir.x) * (180 / M_PI) + 90;

		if (i == snake.tail.size() - 1) {
			SDL_RenderCopyEx(renderer, gameTexs.tailTex, NULL, &r, angle, NULL, SDL_FLIP_NONE);
		}
		else {
			SDL_RenderCopyEx(renderer, gameTexs.bodyTex, NULL, &r, angle, NULL, SDL_FLIP_NONE);
		}
	}

	SDL_RenderPresent(renderer);
}
void update(Snake& snake, Vec2& apple) {
	snake.head.x += snake.dir.x;
	snake.head.y += snake.dir.y;

	snake.tail.insert(snake.tail.begin(), { snake.head, snake.dir });

	if (snake.head.x == apple.x && snake.head.y == apple.y) {
		apple = pickApplePos(snake);
		snake.length++;
	}

	for (int i = 1; i < snake.tail.size() - snake.length; i++) {
		snake.tail.erase(snake.tail.end()-1);
	}

	if (snake.head.x >= WIDTH/RES || snake.head.x < 0 ||
		snake.head.y >= HEIGHT/RES || snake.head.y < 0) {
		
		snake.head = { WIDTH / 2 / RES, HEIGHT / 2 / RES };
		snake.tail.clear();
		snake.dir = { 0, 0 };
		snake.length = 0; 
	}
	for (int i = 1; i < snake.tail.size(); i++) {
		if (snake.head.x == snake.tail[i].pos.x && snake.head.y == snake.tail[i].pos.y) {
			snake.head = { WIDTH / 2 / RES, HEIGHT / 2 / RES };
			snake.tail.clear();
			snake.dir = { 0, 0 };
			snake.length = 0;
		}
	}
}

void handleEvents(Game& game, Snake& snake) {
	
	SDL_Event e;
	SDL_PollEvent(&e);
	switch (e.type) {
	case SDL_QUIT:
		game.isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_UP) {
			snake.dir.y = -1;
			snake.dir.x = 0;
 		} 
		else if(e.key.keysym.sym == SDLK_DOWN) {
			snake.dir.y = 1;
			snake.dir.x = 0;
		}
		else if (e.key.keysym.sym == SDLK_LEFT) {
			snake.dir.y = 0;
			snake.dir.x = -1;
		}
		else if (e.key.keysym.sym == SDLK_RIGHT) {
			snake.dir.y = 0;
			snake.dir.x = 1;
		}
	default:
		break;
	}
}

void clean(Game game) {
	SDL_DestroyWindow(game.window);
	SDL_DestroyRenderer(game.renderer);
	SDL_Quit();
}

bool checkPos(Vec2 pos, std::vector<Body> tail) {
	bool found = true;
	for (int i = 0; i < tail.size(); i++) {
		if (pos.x == tail[i].pos.x && pos.y == tail[i].pos.y) {
			found = false;
		}
	}
	return found;
}

Vec2 pickApplePos(Snake snake) {
	Vec2 posTry; 
	bool posFound = false;

	while (!posFound) {
		posTry = { (std::rand() % (WIDTH - RES)) / RES, (std::rand() % (HEIGHT - RES)) / RES };
		if (checkPos(posTry, snake.tail) && posTry.x != snake.head.x && posTry.y != snake.head.y) {
			posFound = true;
		}
	}
	return posTry;
}

