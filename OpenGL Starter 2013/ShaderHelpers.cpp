#include "ShaderHelpers.h"

using namespace std;

//Load a text file for glsl shaders.
string ShaderHelper::loadTextFile(const char* file)
{
	string shaderText;

	ifstream reader;
	string line;

	reader.open(file);
	if (reader.is_open())
	{
		while (getline(reader, line))
		{
			shaderText.append(line);
			shaderText.append("\n");
		}
		reader.close();
	}
	else
	{
		return "0";
	}

	return shaderText;
}

//Load and compile shaders.
GLuint ShaderHelper::loadShader(const char* file, GLenum shaderType)
{
	//If load failed, return 0.
	string shaderText = loadTextFile(file).c_str();
	if (shaderText == "0")
	{
		return 0;
	}


	GLuint shaderIndex = glCreateShader(shaderType);

	const char* temp = shaderText.c_str();
	glShaderSource(
		shaderIndex,
		1,
		&temp,
		0);
	glCompileShader(shaderIndex);

	GLint compiled;

	//Error checking for compilation.
	glGetShaderiv(shaderIndex, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE)
	{
		GLint length = 0;
		glGetShaderiv(shaderIndex, GL_INFO_LOG_LENGTH, &length);
		char* logData = new char[length];
		glGetShaderInfoLog(
			shaderIndex,
			length,
			0,
			logData);
		cout << "COMPILE SHADER FAILED:" << endl;
		cout << logData << endl;
		delete[] logData;
		return 0;
	}

	return shaderIndex;
}

//Create shader program.
GLuint ShaderHelper::loadShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	//Vertex shader
	GLuint resultVertex = loadShader(vertexFile, GL_VERTEX_SHADER);
	if (resultVertex == 0)
	{
		cout << "FAILED LOAD: " << vertexFile << endl;
		return 0;
	}

	//Fragment shader
	GLuint resultShader = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	if (resultShader == 0)
	{
		cout << "FAILED LOAD: " << fragmentFile << endl;
		return 0;
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, resultVertex);
	glAttachShader(program, resultShader);

	glLinkProgram(program);

	GLint linked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);

	//Error checking for program.
	if (linked == GL_FALSE)
	{
		GLint length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* logData = new char[length];
		glGetProgramInfoLog(
			program,
			length,
			0,
			logData);
		cout << "LINK PROGRAM FAILED:" << endl;
		cout << logData << endl;
		delete[] logData;
		return 0;
	}

	return program;
}

void ShaderHelper::setShaderColor(GLuint program, const char* name, float red, float green, float blue)
{
	glGetUniformLocation(program, name);
	glProgramUniform4f(program, 0, red, green, blue, 1.0f);
}