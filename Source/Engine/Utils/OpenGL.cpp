#include "stdafx.h"
#include "OpenGL.h"
#include "Log.h"

bool CheckGLError()
{
	GLenum error = glGetError();

	switch(error)
	{
		case GL_NO_ERROR: 
			return false;
		case GL_INVALID_OPERATION:
			Av::Log::log("OpenGL error: invalid operation\n");
			return true;
		case GL_INVALID_ENUM:
			Av::Log::log("OpenGL error: invalid enum\n");
			return true;
		case GL_INVALID_VALUE:
			Av::Log::log("OpenGL error: invalid value\n");
			return true;
		//case GL_STACK_OVERFLOW:
		//	Av::Log::log("OpenGL error: stack overflow\n");
		//	return true;
		//case GL_STACK_UNDERFLOW:
		//	Av::Log::log("OpenGL error: stack underflow\n");
		//	return true;
		case GL_OUT_OF_MEMORY:
			Av::Log::log("OpenGL error: out of memory\n");
			return true;
		default:
			return false;
	}
}

bool CheckGLError(char *loc)
{
	GLenum error = glGetError();

	switch(error)
	{
		case GL_NO_ERROR: 
			return false;
		case GL_INVALID_OPERATION:
			Av::Log::log("OpenGL error: invalid operation (%s)\n", loc);
			return true;
		case GL_INVALID_ENUM:
			Av::Log::log("OpenGL error: invalid enum (%s)\n", loc);
			return true;
		case GL_INVALID_VALUE:
			Av::Log::log("OpenGL error: invalid value (%s)\n", loc);
			return true;
		//case GL_STACK_OVERFLOW:
		//	Av::Log::log("OpenGL error: stack overflow (%s)\n", loc);
		//	return true;
		//case GL_STACK_UNDERFLOW:
		//	Av::Log::log("OpenGL error: stack underflow (%s)\n", loc);
		//	return true;
		case GL_OUT_OF_MEMORY:
			Av::Log::log("OpenGL error: out of memory (%s)\n", loc);
			return true;
		default:
			return false;
	}
}

void ProgramLog(GLuint program)
{
	GLint result = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result == GL_TRUE)
		Av::Log::log("Program link successfull\n");
	else
		Av::Log::log("Program link failed\n");

	int logLength = 0;
	char log[1024];

	glGetProgramInfoLog(program, 1024, &logLength, log);

	if (logLength > 0)
		Av::Log::log("Shader program log:\n%s\n", log);
}

void ShaderLog(GLuint shader)
{
	GLint result = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_TRUE)
		Av::Log::log("Shader compile successfull\n");
	else
		Av::Log::log("Shader compile failed\n");

	int logLength = 0;
	char log[1024];

	glGetShaderInfoLog(shader, 1024, &logLength, log);

	if (logLength > 0)
		Av::Log::log("Shader log:\n%s\n", log);
}