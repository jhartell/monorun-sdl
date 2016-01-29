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
#ifndef MONORUN_H
#define MONORUN_H

#include <SDL.h>

// Window settings
#define WINDOW_TITLE "Monorun"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Game state
enum GameMode {
	MODE_INACTIVE,
	MODE_STARTSCREEN,
	MODE_RUNNING,
	MODE_DEAD,
	MODE_ENDSCREEN,
};

// Gamestate structure
typedef struct
{
	enum GameMode mode;			// Current game mode
	unsigned short isDragging;	// Player is being dragged
	unsigned int winWidth;		// Current window width
	unsigned int winHeight;		// Current window height
	uint32_t startTime;			// Start time
	uint32_t endTime;			// End time, player dies
} Gamestate;


extern Gamestate gGame;

void ProcessEvents();
void Render();
void MainLoop();
void GameLoop();
void HitTest();

#endif
