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

Vector VectorInit(float x, float y)
{
	Vector r;
	r.x = x;
	r.y = y;
	return r;
}

Vector VectorAdd(Vector v1, Vector v2)
{
	Vector r;
	r.x = v1.x + v2.x;
	r.y = v1.y + v2.y;
	return r;
}

Vector VectorSub(Vector v1, Vector v2)
{
	Vector r;
	r.x = v1.x - v2.x;
	r.y = v1.y - v2.y;
	return r;
}

Vector VectorScale(Vector v, float scale)
{
	Vector r;
	r.x = v.x * scale;
	r.y = v.y * scale;
	return r;
}

float VectorLength(const Vector v)
{
	return sqrt((v.x * v.x) + (v.y * v.y));
}

Vector VectorFlip(Vector v)
{
	Vector r;
	r.x = -(v.x);
	r.y = -(v.y);	
	return r;
}

/**
* Normalize vector v
*/
Vector VectorNorm(Vector v)
{
	Vector r;
	float len = VectorLength(v);
	r.x = v.x / len;
	r.y = v.y / len;
	
	return r;
}

/**
* Calculate dot product of vectors v1 and v2
*/
float VectorDot(Vector v1, Vector v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}
