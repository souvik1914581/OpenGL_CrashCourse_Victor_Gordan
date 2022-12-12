#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Color.h"

int main(int argc, char** argv){
	
	/*Initialise GLFW*/
	glfwInit();

	/*Tell GLFW what OpenGL version we are using*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	/*Tell which OpenGL profile to use
	Core = Modern OpenGL package of functions
	Compatibility = Legacy */
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*Create a Window*/
	Window winProperties{ 1920,1080,"Doom 3D" };
	GLFWwindow* window = glfwCreateWindow(winProperties.Width(),winProperties.Height(),winProperties.Title(), nullptr, nullptr);
	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	/*use the created window.
	Make the new window part of the current context*/
	glfwMakeContextCurrent(window);

	/*load OpenGL using GLAD*/
	gladLoadGL();

	/*Tell OpenGL about our viewPort*/
	glViewport(0, 0, winProperties.Width(),winProperties.Height());

	/*Tell OpenGL to clear the Back Buffer colors*/
	Color skyColor{ 0.7f, 10.0f, 200.0f, 0.5f };
	Color brownishColor{ 200.0f, 10.0f, 0.7f, 1.0f };
	glClearColor(skyColor.Red(),skyColor.Green(),skyColor.Blue(),skyColor.Alpha());
	glClear(GL_COLOR_BUFFER_BIT);

	/*swap the buffers*/
	glfwSwapBuffers(window);

	bool toggle = true;
	while (!glfwWindowShouldClose(window)){
		/*poll for events*/
		glfwPollEvents();
		
		if (toggle) {
			glClearColor(skyColor.Red(), skyColor.Green(), skyColor.Blue(), skyColor.Alpha());
			glClear(GL_COLOR_BUFFER_BIT);
			toggle = false;
		}
		else {
			glClearColor(brownishColor.Red(), brownishColor.Green(), brownishColor.Blue(), brownishColor.Alpha());
			glClear(GL_COLOR_BUFFER_BIT);
			toggle = true;
		}
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);

	/*Terminate GLFW*/
	glfwTerminate();
	return 0;
}