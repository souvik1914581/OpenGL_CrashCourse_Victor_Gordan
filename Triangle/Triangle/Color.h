#pragma once
#include <glad/glad.h>
#include <vector>
struct Color {
	GLfloat r, g, b;
	GLfloat alpha = 1.0f;
	const GLfloat& Red() const {
		return r;
	}
	const GLfloat& Green() const {
		return g;
	}
	const GLfloat& Blue() const {
		return b;
	}

	const GLfloat& Alpha() const {
		return alpha;
	}
};

const std::vector<Color> vibGyor{
	{	148,0,211	},
	{	74,0,130	},
	{	0,0,255		},
	{	0,255,0		},
	{	255,255,0	},
	{	255,127,0	},
	{	255,0,0		}	
};