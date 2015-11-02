#pragma once
#include <GL/glew.h>		//GLEW.
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ShaderHelper
{
	public:
		string loadTextFile(const char* file);
		GLuint loadShader(const char* file, GLenum shaderType);
		GLuint loadShaderProgram(const char* vertexFile, const char* fragmentFile);
	private:
};