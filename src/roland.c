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
#include <stdint.h>
#include <string.h>
#include "vector.h"
#include "monorun.h"
#include "roland.h"
#include "player.h"


// Pointer to the first Roland struct
static Roland *rolandList = NULL;
// Last Roland spawn time (ms)
static uint32_t rolandLastSpawnTime = 0;


/**
* Get the first Roland in the list
*/
Roland *GetFirstRoland()
{
	return rolandList;
}

/**
* Get number of Rolands currently in game
*/
int GetRolandCount()
{
	int count = 0;
	
	Roland *r = GetFirstRoland();
	while(r != NULL) {
		count++;
		r = r->next;
	}
	
	return count;
}

/**
* Spawn a new Roland
* This function checks the spawn interval internally, and is
* meant to be called from the game loop.
*/
void RolandSpawn()
{
	Roland *r;
	uint32_t cTime = SDL_GetTicks();

	// Do not spawn until a set amount of time has passed since last spawn
	if((rolandLastSpawnTime > 0) && cTime < (rolandLastSpawnTime + ROLAND_SPAWN_INTERVAL)) {
		return;
	}

	rolandLastSpawnTime = cTime;
	r = RolandAdd();
	
	// Randomize large
	r->isLarge = (rand() % 2 == 0) ? 1 : 0;
	if(r->isLarge)
		r->radius = ROLAND_LARGE_RADIUS;
	else
		r->radius = ROLAND_RADIUS;
	
	// Set position
	r->position = VectorInit(-(r->radius/2), -(r->radius/2));

	// Randomize speed (used as acceleration in units per second)
	r->speed = ((rand()%800)+100);

	//printf("Roland Spawn %ld, Large: %d, Speed: %f, Total: %d\n", rolandLastSpawnTime, r->isLarge, r->speed, GetRolandCount());
}


/**
* Add a new Roland to the game
*/
Roland *RolandAdd()
{
	Roland *roland;
	
	roland = malloc(sizeof(Roland));
	if(roland == NULL) {
		fprintf(stderr, "malloc failed\n");
		exit(0);
	}
	
	memset(roland, 0, sizeof(Roland));

	roland->next = rolandList;
	rolandList = roland;
	
	return roland;
}


/**
* Remove a Roland from the game
*
*/
void RolandTerminate(Roland *roland)
{
	// Not implemented yet
}


/**
* Terminate all Rolands
*
*/
void RolandTerminateAll()
{
	Roland *p = rolandList;
	Roland *n;

	while(p != NULL) {
		n = p->next;
		free(p);
		p = n;
	}
}


/**
* Animate all Rolands, called from game loop
*/
void RolandAnimateAll()
{
	Roland *r = GetFirstRoland();
	while(r != NULL) {	
		RolandAnimate(r);
		r = r->next;
	}
}


/**
* Animate a specific Roland, advance against target
*/
void RolandAnimate(Roland *roland)
{
	float moveDistance;
	float distanceLeft;
	float dt;
	
	// Not moving, generate new target position
	if(roland->isMoving == 0)
	{
		// Attack player
		if(roland->attackFlag) {
			RolandMoveTo(roland, gPlayer.position.x, gPlayer.position.y);
			roland->attackFlag = 0;
			//printf("Roland attack!\n");
			return;
		}
		
		RolandMoveTo(
			roland,
			roland->radius + (rand() % (gGame.winWidth - roland->radius*2)),
			roland->radius + (rand() % (gGame.winHeight - roland->radius*2))
		);
		
		return;
	}

	// Calculate dt in seconds
	dt = (float)(SDL_GetTicks() - roland->lastUpdate) / 1000;
	roland->lastUpdate = SDL_GetTicks();
	//printf("dt: %f\n", dt);
	
	
	// Add velocity vector to position
	roland->position = VectorAdd(roland->position, VectorScale(roland->velocity, dt));
	//printf("Pos: %f %f\n", roland->position.x, roland->position.y);
	
	// Add deceleration
	moveDistance = VectorLength(roland->target);
	distanceLeft = VectorLength(VectorSub(roland->end, roland->position));
	//printf("%f %f\n", moveDistance, distanceLeft);
	
	if(distanceLeft < (moveDistance/2)) {
		// Decelerate
		Vector d = VectorFlip(roland->acceleration);
		roland->velocity = VectorAdd(roland->velocity, VectorScale(d, dt));
	} else {
		// Add acceleration to velocity
		roland->velocity = VectorAdd(roland->velocity, VectorScale(roland->acceleration, dt));
	}
	
	// Check overshoot
	if(VectorDot(roland->target, roland->velocity) < 0) {
		roland->isMoving = 0;
	}
}


/**
* Move to a new position
*/
void RolandMoveTo(Roland *roland, unsigned int x, unsigned int y)
{
	roland->isMoving = 1;
	roland->lastUpdate = SDL_GetTicks();
	
	roland->end = VectorInit((float)x, (float)y);
	roland->target = VectorSub(roland->end, roland->position);
	roland->velocity = VectorInit(0, 0);
	
	// Normalize target vector and scale by speed
	// acceleration in units per second
	roland->acceleration = VectorScale(VectorNorm(roland->target), roland->speed);
	
	//printf("Start position: %f %f\n", roland->position.x, roland->position.y);
	//printf("End pos: %f %f\n", roland->end.x, roland->end.y);
	//printf("Target vect: %f %f\n", roland->target.x, roland->target.y);
	//printf("Acceleration: %f - %f %f (%f)\n", roland->speed, roland->acceleration.x, roland->acceleration.y, VectorLength(roland->acceleration));
}




/**
* Send a random Roland to attack the player
*/
void RolandRandomAttack()
{
	int count = GetRolandCount();
	int i = 0;
	int target = rand() % count;
	
	Roland *r = GetFirstRoland();
	while(r != NULL) {
		if(i++ == target) {
			// Set attack flag
			r->attackFlag = 1;
			break;
		}
		
		r = r->next;
	}
}

