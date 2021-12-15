/*******************************************************************************
* 
* FILENAME : vector.h
*
* DESCRIPTION : Header file containing vector structs and function headers
*
* AUTHOR : filipang 
* 
* START DATE :		16/11/2021
*
*******************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector2i
{
	union
	{
		struct
		{
			int w;
			int h;
		};
		struct
		{
			int x;
			int y;
		};
	};
} Vector2i;

typedef struct Vector2f
{
	union
	{
		struct
		{
			float w;
			float h;
		};
		struct
		{
			float x;
			float y;
		};
	};
} Vector2f;

Vector2f vector2f(float x, float y);
Vector2i vector2i(int x, int y);

Vector2f vector2fMinus(Vector2f v1, Vector2f v2); 
Vector2i vector2iMinus(Vector2i v1, Vector2i v2);

Vector2f vector2fMinus(Vector2f v1, Vector2f v2); 
Vector2i vector2iMinus(Vector2i v1, Vector2i v2);

Vector2f vector2iRoundTo2f(Vector2i v);
Vector2i vector2fRoundTo2i(Vector2f v);

Vector2f vector2fDivide(Vector2f v, float f);
Vector2i vector2iDivide(Vector2i v, int f);

Vector2f vector2fMultiply(Vector2f v, float f);
Vector2i vector2iMultiply(Vector2i v, int f);

float vector2fMagnitude(Vector2f vector);
Vector2f vector2fNormalize(Vector2f vector);

Vector2f vector2fDown();
Vector2f vector2fUp();
Vector2f vector2fLeft();
Vector2f vector2fRight();
Vector2f vector2fZero();

Vector2i vector2iDown();
Vector2i vector2iUp();
Vector2i vector2iLeft();
Vector2i vector2iRight();
Vector2i vector2iZero();

int vectorGetFacingDirection(Vector2f delta);

#endif
