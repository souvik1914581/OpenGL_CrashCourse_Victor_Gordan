#pragma once
#include <glad/glad.h>
#include <string>

struct Window {
	int width, height;
	std::string title;
	const int& Width() const {
		return width;
	}
	const int& Height() const {
		return height;
	}
	const char* Title() const {
		return title.c_str();
	}
};