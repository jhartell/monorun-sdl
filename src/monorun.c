/*
* Monorun-sdl
* An SDL game based on the Javascript game Monorun! by Benjamin Horn
* https://github.com/beije/monorun
*
* Copyright (C) 2016  Johnny Härtell
* https://github.com/jhartell/monorun-sdl
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "monorun.h"
#include "roland.h"
#include "player.h"
#include "vector.h"

static SDL_Window *gWindow;
static SDL_Renderer *gRenderer;

Gamestate gGame = {
	MODE_INACTIVE, 0, 0, 0, 0, 0
};


/**
* Process events
*/
void ProcessEvents()
{
	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_WINDOWEVENT_CLOSE:
			case SDL_QUIT:
				exit(0);
			break;
			
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						exit(0);
					break;
				}
			break;
			
			// Mouse button down
			case SDL_MOUSEBUTTONDOWN:
				gGame.isDragging = 1;
				PlayerSetPosition(event.motion.x, event.motion.y);
			break;
			
			// Mouse button up
			case SDL_MOUSEBUTTONUP:
				gGame.isDragging = 0;
			break;
			
			// Mouse motion
			case SDL_MOUSEMOTION:
				if(gGame.isDragging == 1) {
					PlayerSetPosition(event.motion.x, event.motion.y);
				}
			break;
		}
	}
}


/*
* Render display
*/
void Render()
{
	int i;
	Roland *roland;
	SDL_Surface *surface, *surface2;
	SDL_Texture *texture, *texture2;
	SDL_Rect rect;
	
	
	// Draw background color
	SDL_SetRenderDrawColor(gRenderer, 22, 27, 30, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(gRenderer);
	
	// Draw player
	surface = IMG_Load("graphics/player.png");
	if(!surface) {
		printf("IMG_Load() failed: %s\n", SDL_GetError());
		exit(1);
	}
	
	rect.x = gPlayer.position.x-(gPlayer.radius);
	rect.y = gPlayer.position.y-(gPlayer.radius);
	rect.w = gPlayer.radius*2;
	rect.h = gPlayer.radius*2;

	texture = SDL_CreateTextureFromSurface(gRenderer, surface);
	SDL_RenderCopy(gRenderer, texture, NULL, &rect);
	
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	

	// Draw lines connecting Rolands
	i = 0;
	roland = GetFirstRoland();
	
	if(GetRolandCount() % 2 == 1) {
		if(roland != NULL) {
			roland = roland->next;
		}
	}
	
	SDL_SetRenderDrawColor(gRenderer, 27, 44, 49, SDL_ALPHA_OPAQUE);
	while(roland != NULL) {
		if(roland->next != NULL && i++%2==0) {
			SDL_RenderDrawLine(gRenderer, roland->position.x, roland->position.y ,roland->next->position.x, roland->next->position.y);
		}
		
		roland = roland->next;
	}
	
	// Draw Rolands
	surface = IMG_Load("graphics/roland_small.png");
	if(!surface) {
		printf("IMG_Load() failed: %s\n", SDL_GetError());
		exit(1);
	}
	
	surface2 = IMG_Load("graphics/roland_large.png");
	if(!surface2) {
		printf("IMG_Load() failed: %s\n", SDL_GetError());
		exit(1);
	}
	texture = SDL_CreateTextureFromSurface(gRenderer, surface);
	texture2 = SDL_CreateTextureFromSurface(gRenderer, surface2);
	
	roland = GetFirstRoland();
	
	while(roland != NULL) {
		rect.x = roland->position.x-(roland->radius);
		rect.y = roland->position.y-(roland->radius);
		rect.w = roland->radius*2;
		rect.h = roland->radius*2;
		
		SDL_RenderCopy(gRenderer, (roland->isLarge ? texture2 : texture), NULL, &rect);
				
		// Debug lines
		//SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		//SDL_RenderDrawLine(gRenderer, roland->position.x, roland->position.y ,roland->end.x, roland->end.y);
		
		roland = roland->next;
	}
	
	SDL_FreeSurface(surface);
	SDL_FreeSurface(surface2);
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(texture2);

	// Render screen
	SDL_RenderPresent(gRenderer);
}

/**
* Main loop
*/
void MainLoop()
{
	// Todo: Implement start and end screens
	if(gGame.mode == MODE_RUNNING) {
		gGame.startTime = SDL_GetTicks();
		GameLoop();
	}
}


/**
* Game loop
*/
void GameLoop()
{
	while(gGame.mode == MODE_RUNNING)
	{
		// Update window size
		SDL_GetWindowSize(gWindow, &gGame.winWidth, &gGame.winHeight);
		
		// Process events
		ProcessEvents();
		
		// Spawn new Rolands
		RolandSpawn();
		
		// Animate Rolands
		RolandAnimateAll();
		
		// Perform hit test
		HitTest();
		
		// Check if player is standing still
		if(PlayerGetStillTime() > ROLAND_ATTACK_LIMIT) {
			RolandRandomAttack();
			PlayerResetStillTime();
		}
		
		// Render screen
		Render();
	}
}

/**
* Hit test
*/
void HitTest()
{
	Roland *roland;
	float distance;
	
	roland = GetFirstRoland();
	
	while(roland != NULL) {
	
		distance = VectorLength(VectorSub(gPlayer.position, roland->position));

		if(distance < (roland->radius + gPlayer.radius)) {
			gGame.mode = MODE_DEAD;
			gGame.endTime = SDL_GetTicks();

			// Print game time and allow the game to quit
			printf("You survived for %d ms\n", (gGame.endTime - gGame.startTime));
			break;
		}
		
		roland = roland->next;
	}
}

/**
* Main entry point
*/
int main(int argc, char *argv[])
{
	// Seed random number generator
	srandom(time(NULL));
	
	// Init SDL
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
		fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	// Create window
	int win_flags = 0;
	// Todo: add support for fullscreen
	//win_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	win_flags |= SDL_WINDOW_RESIZABLE;
	
	gWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, win_flags);
	if(gWindow == NULL) {
		fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
		return 1;
	}
	
	// Create renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if(gRenderer == NULL) {
		fprintf(stderr, "SDL_CreateRenderer error: %s\n", SDL_GetError());
		return 1;
	}
	
	// Init game data
	gGame.mode = MODE_RUNNING;
	// Get initial window size
	SDL_GetWindowSize(gWindow, &gGame.winWidth, &gGame.winHeight);
	
	// Init player
	PlayerInit();
	
	// Enter main loop
	MainLoop();
	
	// Exit SDL
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	SDL_Quit();
	
	return 0;
}
