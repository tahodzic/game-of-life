#pragma once
#include "SDL.h"

#pragma once

#ifndef SDLDRAWER_H
#define SDLDRAWER_H

using namespace std;

class SDLdrawer
{
public:
	SDLdrawer(void);
	~SDLdrawer(void);
	void setupScreen(void);
	void drawPixel(int posX, int posY, bool alive);
	void drawGraphics(unsigned char[]);
	SDL_Event event;
    const static int rectX = 5;
	const static int rectY = 5;
	const static int systemSize = 640 * 320 / (rectX * rectY);
	const static int numCol = 640 / SDLdrawer::rectX;
private:
	SDL_Renderer * renderer;
	SDL_Window* MainWindow;
	SDL_Texture* sdlTexture;
	SDL_Rect r;
	const int screenWidth = 640;
	const int screenHeight = 320;

};

#endif