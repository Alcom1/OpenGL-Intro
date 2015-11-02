#include <iostream>
#include <GL/glew.h>		//GLEW.
#include <GLFW/glfw3.h>		//GLFW manages windows and user input.
#include "ShaderHelpers.h"

//Global Variables
GLuint indexVAO;								//Index for vertex array object.
GLuint indexVBO;								//Index for vertex buffer object.
const GLsizei countVertex = 3;					//Number of verticies
const GLsizei countComponent = countVertex * 2;	//Number of vertex components.y

//Initialization
void init()
{
	std::cout << "init!" << std::endl;		//Debug print initalization.
	glClearColor(							//Sets the color for clear.
		(13.0f / 255.0f),
		(105.0f / 255.0f),
		(171.0f / 255.0f),
		0.0f);

	//Shaders
	ShaderHelper shaderHelper;
	GLuint program = shaderHelper.loadShaderProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
	if (program != 0)
	{
		shaderHelper.setShaderColor(program, "color", 0.4f, 1.0f, 1.0f);
		glUseProgram(program);
	}

	//VAO
	glGenVertexArrays(1, &indexVAO);		//Generate a vertex array object.
	glBindVertexArray(indexVAO);			//Bind the vertex array object as the active object.

	//VBO
	glGenBuffers(1, &indexVBO);					//Generates a vertex buffer object.
	glBindBuffer(GL_ARRAY_BUFFER, indexVBO);	//Bind the vertex buffer object as the active object.

	//Array of verticies
	GLfloat verticies[countComponent] = { 0.5f, 0.6f, 0.4f, -0.7f, -0.8f, -0.2f };

	//Copy data into buffer
	glBufferData(
		GL_ARRAY_BUFFER,	//Target for data
		sizeof(verticies),	//Number of bytes per vertex.
		verticies,			//Data to be copied
		GL_STATIC_DRAW);	//Do not change the data. Optimization for static draws.

	//Describe the layout of the data being copied to the buffer.
	glVertexAttribPointer(
		0,					//Attribute index
		2,					//Number of spacial components
		GL_FLOAT,			//Data type
		GL_FALSE,			//If normalized
		0,					//Bytes between attributes.
		0);					//Byte offset to this attribute.

	//Enable the created attribute.
	glEnableVertexAttribArray(0);
}

//Update
void update()
{
	//std::cout << "update!" << std::endl;	//Debug print update.
}

//Draw
void draw()
{
	//std::cout << "draw" << std::endl;		//Debug print draw.
	glClear(GL_COLOR_BUFFER_BIT);			//Clear the screen.

	glDrawArrays(
		GL_TRIANGLES,
		0,
		countVertex);

	glFlush();								//Peforms all draw calls.
}

//Main
int main()
{
	//Initialize GLFW, terminate if failed.
	if (!glfwInit())
	{
		return -1;
	}

	//Create an OpenGL Window, terminate if failed.
	GLFWwindow * window = glfwCreateWindow(320, 200, "OpenGL App", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -2;
	}

	//Make window current context, similar to user clicking on it.
	glfwMakeContextCurrent(window);

	//Sets up GLEW
	glewExperimental = GL_TRUE;		//Makes sure all gwafix cards will be supported.
	if (glewInit() != GLEW_OK)		//Check if GLEW initialized sucessfully, terminate if not.
	{
		glfwTerminate();
		return -1;
	}

	init();							//Initialization before loop
	while (!glfwWindowShouldClose(window))	//Loop
	{
		update();					//Update in loop
		draw();						//Draw in loop
		glfwSwapBuffers(window);	//Swap previous frame for new frame.
		glfwPollEvents();			//Poll events such as windows closing and key presses.
	}

	//End
	glfwTerminate();
	return 0;
}