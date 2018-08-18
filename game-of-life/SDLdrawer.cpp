#include "stdafx.h"
#include "SDLdrawer.h"

SDLdrawer::SDLdrawer(void)
{
}


SDLdrawer::~SDLdrawer(void)
{
}

void SDLdrawer::setupScreen(void)
{
	//Initialization
	SDL_Init(SDL_INIT_VIDEO);

	//Window
	MainWindow = SDL_CreateWindow("Game of Life",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		screenWidth, screenHeight,
		SDL_WINDOW_RESIZABLE
	);

	//Rect size
	r.w = rectX;
	r.h = rectY;

	//Renderer
	renderer = SDL_CreateRenderer(MainWindow, -1, 0);

	// Create texture that stores frame buffer
	sdlTexture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_TARGET,
		screenWidth, screenHeight);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer); // fill the scene with black
	SDL_RenderPresent(renderer); // copy to screen
}

//Function for drawing the initial cells
void SDLdrawer::drawPixel(int posX, int posY, bool alive)
{
	r.x = posX;
	r.y = posY;

	SDL_SetRenderTarget(renderer, sdlTexture);

	//Clean
	//SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	//SDL_RenderClear(renderer);

	//Draw rect
	SDL_RenderDrawRect(renderer, &r);

	//Set color: white = alive, black = dead (not seeable)
	alive ? SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF) : SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderFillRect(renderer, &r);
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, sdlTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

//Update function: after each generation the entire system is redrawn
void SDLdrawer::drawGraphics(unsigned char curSystem[]) {
	bool empty = true;

	//rect array to be displayed on screen
	SDL_Rect rect[systemSize];
	for (int i = 0; i < systemSize; ++i) {
		if (curSystem[i] == 1) {

			rect[i].x = (i % numCol) * rectX;
			rect[i].y = (int(i / numCol)) * rectY;
			rect[i].h = rectX;
			rect[i].w = rectY;
		}
		if (curSystem[i] == 0) {
			rect[i].x = 0;
			rect[i].y = 0;
			rect[i].h = 0;
			rect[i].w = 0;
		}
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // the rect color (black, background)
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // the rect color (solid white)
	SDL_RenderFillRects(renderer, rect, systemSize);
	SDL_RenderPresent(renderer);

}
