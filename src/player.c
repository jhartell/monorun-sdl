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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monorun.h"
#include "player.h"

Player gPlayer = {
	{0, 0},
	PLAYER_RADIUS,
	{0, 0},
	0
};

/**
* Init player
*/
void PlayerInit()
{
	PlayerSetPosition(
		(gGame.winWidth/2),
		(gGame.winHeight/2)
	);		
}

/**
* Set player position
*/
void PlayerSetPosition(unsigned int x, unsigned int y)
{
	gPlayer.position.x = x;
	gPlayer.position.y = y;
	
	if(x != gPlayer.lastPosition.x || y != gPlayer.lastPosition.y) {
		gPlayer.lastMoveTime = SDL_GetTicks();		
	}
}

/**
* Get time the player has been standing still
*/
uint32_t PlayerGetStillTime()
{
	return (SDL_GetTicks() - gPlayer.lastMoveTime);
}

/**
* Reset time the player has been standing still
*/
void PlayerResetStillTime()
{
	gPlayer.lastMoveTime = SDL_GetTicks();
}
