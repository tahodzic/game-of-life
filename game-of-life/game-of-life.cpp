// game-of-life.cpp : アプリケーションのエントリ ポイントを定義します。
//
/* by Damir Hodzic 
Rules:
Any live cell with fewer than two live neighbors dies, as if by under population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by overpopulation.
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
*/

#include "stdafx.h"
#include <iostream>
#include "SDLdrawer.h"
#include <conio.h>

SDLdrawer myDrawer;

int main(int argc, char* argv[])
{
	myDrawer.setupScreen();
	unsigned char curSystem[SDLdrawer::systemSize];
	unsigned char nexSystem[SDLdrawer::systemSize];
	for (int i = 0; i < SDLdrawer::systemSize; i++)
	{
		curSystem[i] = 0;
	}
	cout << "Plant the initial cells by hovering over the right window. After you've finished hit enter in the command line (here).";
	while (!_kbhit())
	{
		while (SDL_PollEvent(&myDrawer.event))
		{
			if (myDrawer.event.type == SDL_MOUSEBUTTONDOWN || myDrawer.event.type == SDL_MOUSEMOTION && myDrawer.event.motion.state & SDL_BUTTON_LMASK)
			{
				int x = myDrawer.event.button.x;
				int y = myDrawer.event.button.y;
				if (curSystem[x / SDLdrawer::rectX + int(y / SDLdrawer::rectY) * SDLdrawer::numCol] == 0)
					curSystem[x / SDLdrawer::rectX + int(y / SDLdrawer::rectY) * SDLdrawer::numCol] = 1;
				x -= x % SDLdrawer::rectX;
				y -= y % SDLdrawer::rectY;
				myDrawer.drawPixel(x, y, true);
			}
			if (myDrawer.event.type == SDL_QUIT)
				exit(0);
			//switch (myDrawer.event.type)
			//{
			//case SDL_MOUSEMOTION: 
			//{
			//	case SDL_MOUSEBUTTONDOWN: {
					//int x = myDrawer.event.button.x;
					//int y = myDrawer.event.button.y;
					//if (curSystem[x / SDLdrawer::rectX + int(y / SDLdrawer::rectY) * SDLdrawer::numCol] == 0)
					//	curSystem[x / SDLdrawer::rectX + int(y / SDLdrawer::rectY) * SDLdrawer::numCol] = 1;
					//x -= x % SDLdrawer::rectX;
					//y -= y % SDLdrawer::rectY;
					//myDrawer.drawPixel(x, y, true);
			//	}
			//	break;
			//}
			//default: break;
			//}
		}
	}

	int neighborCnt = 0;

	for (int i = 0; i < SDLdrawer::systemSize; i++)
	{
		nexSystem[i] = curSystem[i];
	}

	myDrawer.drawGraphics(curSystem);
	while (1)
	{
		while (SDL_PollEvent(&myDrawer.event) >= 0)
		{
			for (int i = 0; i < SDLdrawer::systemSize; i++)
			{
				//Count neighbor cells that are alive

				//left
				if (i > 0)
					if (curSystem[i - 1] == 1) neighborCnt++;

				//top left
				if (curSystem[i - (SDLdrawer::numCol + 1)] == 1) neighborCnt++;

				//up
				if (curSystem[i - SDLdrawer::numCol] == 1) neighborCnt++;

				//top right
				if (curSystem[i - SDLdrawer::numCol + 1] == 1) neighborCnt++;

				//right
				if (i < SDLdrawer::systemSize)
					if (curSystem[i + 1] == 1) neighborCnt++;

				//down right
				if (i < (SDLdrawer::systemSize - SDLdrawer::numCol))
					if (curSystem[i + SDLdrawer::numCol + 1] == 1) neighborCnt++;


				if (i < (SDLdrawer::systemSize - SDLdrawer::numCol))
				{
					//down
					if (curSystem[i + SDLdrawer::numCol] == 1) neighborCnt++;

					//down left
					if (curSystem[i + SDLdrawer::numCol - 1] == 1) neighborCnt++;
				}


				if (curSystem[i] == 1)
				{
					if (neighborCnt < 2 || neighborCnt > 3)
					{
						//kill cell
						nexSystem[i] = 0;
					}
				}
				else
				{
					if (neighborCnt == 3)
					{
						//revive cell
						nexSystem[i] = 1;
					}
				}
				neighborCnt = 0;


			}

			myDrawer.drawGraphics(nexSystem);
			SDL_Delay(50);
			for (int i = 0; i < SDLdrawer::systemSize; i++)
			{
				curSystem[i] = nexSystem[i];
			}

			if (myDrawer.event.type == SDL_QUIT)
				exit(0);
		}
	}
	return 0;
}
