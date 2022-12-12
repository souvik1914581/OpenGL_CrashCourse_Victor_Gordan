#pragma once
#include <glad/glad.h>
struct Color {
	GLfloat r, g, b,alpha;
	const GLfloat& Red() {
		return r;
	}
	const GLfloat& Green() {
		return g;
	}
	const GLfloat& Blue() {
		return b;
	}

	const GLfloat& Alpha() {
		return alpha;
	}
};