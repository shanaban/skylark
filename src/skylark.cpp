#include <SDL2/SDL.h>
#include <iostream>

#include "display.h"
#include "renderer.h"
#include "mem.h"
#include "loader.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

void DrawHeart(DisplayBuffer *buffer)
{
	buffer->Clear();

	for (int x = 0; x < buffer->getWidth(); x++)
	{
		for (int y = 0; y < buffer->getHeight(); y++)
		{
			double xt = (x - 70) / 17.0;
			double yt = (y - 24) / -22.0;
			double exp1 = xt * xt + yt * yt - 1;
			double exp = exp1 * exp1 * exp1 - (xt * xt - yt * yt * yt);
			double thresh = 0.3;
			if (exp <= thresh)
			{
				buffer->Draw(x, y, true);
			}
		}
	}
}

const int WINDOW_WIDTH = 960;
const int WINDOW_HEIGHT = 480;

const int RES_WIDTH = 128;
const int RES_HEIGHT = 64;

const double REFRESH_RATE = 10;

void WindowTest()
{
	DisplayBuffer *displayBuffer = new DisplayBuffer(RES_WIDTH, RES_HEIGHT);
	WindowRenderer *renderer = new WindowRenderer(WINDOW_WIDTH, WINDOW_HEIGHT);

	const double millisPerCycle = 1000 / REFRESH_RATE;
	string s = "sdfASDF";

	// Main loop
	bool quit = false;
	SDL_Event e;
	int factor = 0;
	while (!quit)
	{
		// Process events
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_l)
			{
				DrawHeart(displayBuffer);
			}
		}

		renderer->Render(displayBuffer);
	}
}

const uint16_t MEMORY_SIZE = 16;

int main(int argc, char *argv[])
{
	Memory *memory = new Memory(MEMORY_SIZE);
	RomLoader *loader = new RomLoader();

	string fileName = "../roms/count_test.ch8";
	uint16_t programOffset = 0;

	loader->LoadFromFile(fileName, memory, programOffset);

	return 0;
}