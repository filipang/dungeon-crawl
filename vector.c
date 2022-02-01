/*******************************************************************************
* 
* FILENAME : vector.c
*
* DESCRIPTION : Source file containing vector functions
*
* AUTHOR : filipang 
* 
* START DATE :		16/11/2021
*
*******************************************************************************/

Vector2f vector2f(float x, float y)
{
	Vector2f vec = {x, y};
	return vec;
}

Vector2i vector2i(int x, int y)
{
	Vector2i vec = {x, y};
	return vec;
}

Vector2i vector2iMinus(Vector2i v1, Vector2i v2) 
{
	Vector2i result = 
	{
		v1.x - v2.x,
		v1.y - v2.y
	};
	return result;
}

Vector2f vector2fPlus(Vector2f v1, Vector2f v2) 
{
	Vector2f result = 
	{
		v1.x + v2.x,
		v1.y + v2.y
	};
	return result;
}

Vector2i vector2iPlus(Vector2i v1, Vector2i v2) 
{
	Vector2i result = 
	{
		v1.x + v2.x,
		v1.y + v2.y
	};
	return result;
}

Vector2f vector2fMinus(Vector2f v1, Vector2f v2) 
{
	Vector2f result = 
	{
		v1.x - v2.x,
		v1.y - v2.y
	};
	return result;
}

Vector2f vector2iRoundTo2f(Vector2i v)
{
	Vector2f ret =
	{
		(float) v.x,
		(float) v.y
	};

	return ret;
}

Vector2i vector2fRoundTo2i(Vector2f v)
{
	Vector2i ret =
	{
		(int) round(v.x),
		(int) round(v.y)
	};

	return ret;
}

Vector2f vector2fDivide(Vector2f v, float f)
{
	Vector2f ret = {
		v.x / f,
		v.y / f
	};
	
	return ret;
}

Vector2i vector2iDivide(Vector2i v, int f)
{
	Vector2i ret = {
		v.x / f,
		v.y / f
	};
	
	return ret;
}

Vector2f vector2fMultiply(Vector2f v, float f)
{
	Vector2f ret = {
		v.x * f,
		v.y * f
	};
	
	return ret;
}

Vector2i vector2iMultiply(Vector2i v, int f)
{
	Vector2i ret = {
		v.x * f,
		v.y * f
	};
	
	return ret;
}

float vector2fMagnitude(Vector2f vector)
{
	return sqrt(vector.x*vector.x + vector.y*vector.y);
}

Vector2f vector2fNormalize(Vector2f vector)
{
	return vector2fDivide(vector, vector2fMagnitude(vector));	
}

float vector2fDistance(Vector2f v1, Vector2f v2)
{
	return vector2fMagnitude(vector2fMinus(v1,v2));
}

Vector2f vector2fDown()
{
	Vector2f vector = {0, 1};
	return vector;
}

Vector2f vector2fUp()
{
	Vector2f vector = {0, -1};
	return vector;
}

Vector2f vector2fLeft()
{
	Vector2f vector = {-1, 0};
	return vector;
}

Vector2f vector2fRight()
{
	Vector2f vector = {1, 0};
	return vector;
}

Vector2f vector2fZero()
{
	Vector2f vector = {0, 0};
	return vector;
}

Vector2i vector2iDown()
{
	Vector2i vector = {0, 1};
	return vector;
}

Vector2i vector2iUp()
{
	Vector2i vector = {0, -1};
	return vector;
}

Vector2i vector2iLeft()
{
	Vector2i vector = {-1, 0};
	return vector;
}

Vector2i vector2iRight()
{
	Vector2i vector = {1, 0};
	return vector;
}

Vector2i vector2iZero()
{
	Vector2i vector = {0, 0};
	return vector;
}

// NOTE(filip): This might not be the right place for this function
#define FACE_UP 0
#define FACE_LEFT 1
#define FACE_DOWN 2
#define FACE_RIGHT 3

int vectorGetFacingDirection(Vector2f delta)
{
	if(abs(delta.x) >= abs(delta.y))
	{
		if(delta.x <= 0)
		{
			return FACE_LEFT;
		}
		else
		{
			return FACE_RIGHT;
		}
	}
	else
	{
		if(delta.y <= 0)
		{
			return FACE_UP;
		}
		else
		{
			return FACE_DOWN;
		}
	}
}

float vector2fGetAngle(Vector2f vector)
{
	float result;
	if(vector.x >= 0 && vector.y >= 0)
	{
		result = (180/PI)*atan(vector.y/vector.x);
	}
	else if(vector.x <= 0 && vector.y >= 0)
	{
		vector.x *= -1;
		result = (180/PI)*atan(vector.y/vector.x);
		result = 180 - result;
	}
	else if(vector.x >= 0 && vector.y <= 0)
	{
		vector.y *= -1;
		result = (180/PI)*atan(vector.y/vector.x);
		result = 360 - result;
	}
	else if(vector.x <= 0 && vector.y <= 0)
	{
		vector.x *= -1;
		vector.y *= -1;
		result = (180/PI)*atan(vector.y/vector.x);
		result = result + 180;
	}
	return result;
}
