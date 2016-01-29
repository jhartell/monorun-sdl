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
#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
	float x, y;
} Vector;

Vector VectorInit(float x, float y);
Vector VectorAdd(Vector v1, Vector v2);
Vector VectorSub(Vector v1, Vector v2);
Vector VectorScale(Vector v, float scale);
float VectorLength(const Vector v);
Vector VectorFlip(Vector v);
Vector VectorNorm(Vector v);
float VectorDot(Vector v1, Vector v2);


#endif