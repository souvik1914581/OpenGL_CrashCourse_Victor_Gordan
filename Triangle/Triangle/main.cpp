#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Color.h"

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main(int argc, char** argv){
	
	/*Initialise GLFW*/
	glfwInit();

	/*Tell GLFW what OpenGL version we are using
	In this case we are using 3.3*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	/*Tell which OpenGL profile to use
	Core = Modern OpenGL package of functions
	Compatibility = Legacy */
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	/*Create a Window*/
	Window winProperties{ 1920,1080,"Doom 3D Triangle" };
	GLFWwindow* window = glfwCreateWindow(winProperties.Width(),winProperties.Height(),winProperties.Title(), nullptr, nullptr);
	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	/*use the created window.
	Make the new window part of the current context*/
	glfwMakeContextCurrent(window);

	/*load GLAD so that it configures OpenGL*/
	gladLoadGL();

	/*Tell OpenGL about our viewPort*/
	glViewport(0, 0, winProperties.Width(),winProperties.Height());

	/*Get vertexShader*/
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	/*feed the vertex shader source code*/
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	/*at this point GPU cannot understand the vertexShader src code
	Need to compile it into machine code*/
	glCompileShader(vertexShader);

	/*repeating the above steps for Fragment Shader*/
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	/*need to wrap our new shaders into a Shader program*/
	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	/*Wrap-up/Link the Shader Program*/
	glLinkProgram(shaderProgram);

	/*we are done with the now useless shaders, can be deleted*/
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/*Vertex coordinates for our equilateral triangle*/
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	//lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		//lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f	//upper corner
	};

	/*	CPU->GPU data transfer is slow
		Prefer to send data in batches, called Buffers.
		Not to be confused with Back Buffer, Front Buffer
		Here, we use a Vertex Buffer Object(VBO)*/
	GLuint VAO, VBO;

	/*	tell OpenGL where to find the Vertices
		by using Vertex Array Object(VAO).
		VAO stores pointers to one more VBOs and tells
		OpenGL how to use them
		VAOs exist to quickly shift between different VBOs*/

	/*Generate the VAO and VBO with only 1 object each*/
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	/*now lets bind the VAO, make the VAO the current Vertex Array Object by binding it*/
	glBindVertexArray(VAO);

	/*	Binding in OpenGL -
		Binding an object makes the object the current object.
		Whenever a function fires and modifies the current object,
		it modifies that object aka the Binded object*/

	/*Bind the VBO specifying its a GL_ARRAY_BUFFER */
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/*store our vertices in the buffer*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/*now lets configure VAO so that OpenGL knows how to read the VBO*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	/*Enable the Vertex Attribute so that OpenGL knows how to use it*/
	glEnableVertexAttribArray(0);

	/*Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO
	 and VBO we created with a function*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	/*Tell OpenGL to clear the Back Buffer colors*/
	const Color& windowColor = vibGyor[2];
	glClearColor(windowColor.Red(),windowColor.Green(),windowColor.Blue(),windowColor.Alpha());
	glClear(GL_COLOR_BUFFER_BIT);

	/*swap the buffers*/
	glfwSwapBuffers(window);

	const auto& startTime = glfwGetTime();
	while (!glfwWindowShouldClose(window)){
		
		glClearColor(windowColor.Red(), windowColor.Green(), windowColor.Blue(), windowColor.Alpha());
		glClear(GL_COLOR_BUFFER_BIT);

		/*tell OpenGL which Shader program to use*/
		glUseProgram(shaderProgram);

		/*Bind the VAO so that OpenGL knows how to use it*/
		glBindVertexArray(VAO);

		/*Draw the triangle using the GL_TRIANGLES primitive*/
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/*Swap the Back Buffer with the Front Buffer*/
		glfwSwapBuffers(window);

		/*poll for events*/
		glfwPollEvents();
		
		
	}

	/*Delete all the objects we've created*/
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//Delete window before ending the program
	glfwDestroyWindow(window);

	/*Terminate GLFW*/
	glfwTerminate();
	return 0;
}