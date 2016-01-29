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
#ifndef ROLAND_H
#define ROLAND_H

#define ROLAND_SPAWN_INTERVAL 2000	// Time in milliseconds between each Roland spawn
#define ROLAND_RADIUS 30			// Default Roland radius
#define ROLAND_LARGE_RADIUS 36		// Large Roland radius
#define ROLAND_ATTACK_LIMIT 5000	// Time to stand still before a Roland attacks

#include "vector.h"

typedef struct Roland_t
{
	int radius;		// Radius
	int isLarge;	// Is large
	float speed;	// Speed
	
	int attackFlag;	// Attack the player during the next movement
	
	// Movement properties
	uint32_t lastUpdate;
	int isMoving;	// Is moving
	
	Vector position;
	Vector end;
	Vector target;
	Vector velocity;
	Vector acceleration;

	struct Roland_t *next;
} Roland;


int GetRolandCount();
void RolandRandomAttack();
void RolandSpawn();
Roland *RolandAdd();
void RolandTerminate(Roland *roland);
void RolandTerminateAll();

void RolandAnimateAll();
void RolandAnimate(Roland *roland);
void RolandMoveTo(Roland *roland, unsigned int x, unsigned int y);
Roland *GetFirstRoland();


#endif
