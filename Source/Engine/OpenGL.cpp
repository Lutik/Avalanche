#include "stdafx.h"
#include "OpenGL.h"
#include "Log.h"

//Shaders
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLDETACHSHADERPROC glDetachShader;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLUNIFORM1FPROC glUniform1f;
PFNGLUNIFORM2FPROC glUniform2f;
PFNGLUNIFORM3FPROC glUniform3f;
PFNGLUNIFORM4FPROC glUniform4f;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLUNIFORM2IPROC glUniform2i;
PFNGLUNIFORM3IPROC glUniform3i;
PFNGLUNIFORM4IPROC glUniform4i;
PFNGLUNIFORM1FVPROC glUniform1fv;
PFNGLUNIFORM2FVPROC glUniform2fv;
PFNGLUNIFORM3FVPROC glUniform3fv;
PFNGLUNIFORM4FVPROC glUniform4fv;
PFNGLUNIFORM1IVPROC glUniform1iv;
PFNGLUNIFORM2IVPROC glUniform2iv;
PFNGLUNIFORM3IVPROC glUniform3iv;
PFNGLUNIFORM4IVPROC glUniform4iv;
PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f;
PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f;
PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f;
PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation;
PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

//Misc
PFNGLACTIVETEXTUREPROC glActiveTexture;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
PFNWGLSWAPINTERVALEXTPROC wglSwapInterval;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;
PFNGLPRIMITIVERESTARTINDEXPROC glPrimitiveRestartIndex;

//VBO
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLISBUFFERPROC glIsBuffer;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLBUFFERSUBDATAPROC glBufferSubData;
PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData;
PFNGLMAPBUFFERPROC glMapBuffer;
PFNGLUNMAPBUFFERPROC glUnmapBuffer;
PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv;
PFNGLGETBUFFERPOINTERVPROC glGetBufferPointeriv;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

bool GL_InitShaders()
{
	glCreateProgram = (PFNGLCREATEPROGRAMPROC) SDL_GL_GetProcAddress("glCreateProgram");
	glCreateShader = (PFNGLCREATESHADERPROC) SDL_GL_GetProcAddress("glCreateShader");
	glCompileShader = (PFNGLCOMPILESHADERPROC) SDL_GL_GetProcAddress("glCompileShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC) SDL_GL_GetProcAddress("glShaderSource");
	glDeleteShader = (PFNGLDELETESHADERPROC) SDL_GL_GetProcAddress("glDeleteShader");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC) SDL_GL_GetProcAddress("glDeleteProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC) SDL_GL_GetProcAddress("glAttachShader");
	glDetachShader = (PFNGLDETACHSHADERPROC) SDL_GL_GetProcAddress("glDetachShader");
	glUseProgram = (PFNGLUSEPROGRAMPROC) SDL_GL_GetProcAddress("glUseProgram");
	glLinkProgram = (PFNGLLINKPROGRAMPROC) SDL_GL_GetProcAddress("glLinkProgram");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC) SDL_GL_GetProcAddress("glGetProgramiv");
	glGetShaderiv = (PFNGLGETSHADERIVPROC) SDL_GL_GetProcAddress("glGetShaderiv");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) SDL_GL_GetProcAddress("glGetUniformLocation");
	glUniform1f = (PFNGLUNIFORM1FPROC) SDL_GL_GetProcAddress("glUniform1f");
	glUniform2f = (PFNGLUNIFORM2FPROC) SDL_GL_GetProcAddress("glUniform2f");
	glUniform3f = (PFNGLUNIFORM3FPROC) SDL_GL_GetProcAddress("glUniform3f");
	glUniform4f = (PFNGLUNIFORM4FPROC) SDL_GL_GetProcAddress("glUniform4f");
	glUniform1i = (PFNGLUNIFORM1IPROC) SDL_GL_GetProcAddress("glUniform1i");
	glUniform2i = (PFNGLUNIFORM2IPROC) SDL_GL_GetProcAddress("glUniform2i");
	glUniform3i = (PFNGLUNIFORM3IPROC) SDL_GL_GetProcAddress("glUniform3i");
	glUniform4i = (PFNGLUNIFORM4IPROC) SDL_GL_GetProcAddress("glUniform4i");
	glUniform1fv = (PFNGLUNIFORM1FVPROC)SDL_GL_GetProcAddress("glUniform1fv");
	glUniform2fv = (PFNGLUNIFORM2FVPROC)SDL_GL_GetProcAddress("glUniform2fv");
	glUniform3fv = (PFNGLUNIFORM3FVPROC)SDL_GL_GetProcAddress("glUniform3fv");
	glUniform4fv = (PFNGLUNIFORM4FVPROC)SDL_GL_GetProcAddress("glUniform4fv");
	glUniform1iv = (PFNGLUNIFORM1IVPROC)SDL_GL_GetProcAddress("glUniform1iv");
	glUniform2iv = (PFNGLUNIFORM2IVPROC)SDL_GL_GetProcAddress("glUniform2iv");
	glUniform3iv = (PFNGLUNIFORM3IVPROC)SDL_GL_GetProcAddress("glUniform3iv");
	glUniform4iv = (PFNGLUNIFORM4IVPROC)SDL_GL_GetProcAddress("glUniform4iv");
	glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC) SDL_GL_GetProcAddress("glUniformMatrix2fv");
	glUniformMatrix3fv = (PFNGLUNIFORMMATRIX2FVPROC) SDL_GL_GetProcAddress("glUniformMatrix3fv");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX2FVPROC) SDL_GL_GetProcAddress("glUniformMatrix4fv");
	glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC) SDL_GL_GetProcAddress("glVertexAttrib1f");
	glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC) SDL_GL_GetProcAddress("glVertexAttrib2f");
	glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC) SDL_GL_GetProcAddress("glVertexAttrib3f");
	glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC) SDL_GL_GetProcAddress("glVertexAttrib4f");
	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC) SDL_GL_GetProcAddress("glBindAttribLocation");
	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC) SDL_GL_GetProcAddress("glGetAttribLocation");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) wglGetProcAddress("glVertexAttribPointer");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) SDL_GL_GetProcAddress("glDisableVertexAttribArray");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) SDL_GL_GetProcAddress("glEnableVertexAttribArray");
	glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC) SDL_GL_GetProcAddress("glBindFragDataLocation");
	glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC) SDL_GL_GetProcAddress("glGetFragDataLocation");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) SDL_GL_GetProcAddress("glGetProgramInfoLog");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) SDL_GL_GetProcAddress("glGetShaderInfoLog");

	return true;
}

bool GL_InitMisc()
{
	glActiveTexture = (PFNGLACTIVETEXTUREPROC) SDL_GL_GetProcAddress("glActiveTexture");
	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) SDL_GL_GetProcAddress("glGenerateMipmap");
	glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC) SDL_GL_GetProcAddress("glCompressedTexImage2D");
	glPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC) SDL_GL_GetProcAddress("glPrimitiveRestartIndex");

	return true;
}

bool GL_InitVBO()
{
	glBindBuffer = (PFNGLBINDBUFFERPROC) SDL_GL_GetProcAddress("glBindBuffer");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) SDL_GL_GetProcAddress("glDeleteBuffers");
	glGenBuffers = (PFNGLGENBUFFERSPROC) SDL_GL_GetProcAddress("glGenBuffers");
	glIsBuffer = (PFNGLISBUFFERPROC) SDL_GL_GetProcAddress("glIsBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC) SDL_GL_GetProcAddress("glBufferData");
	glBufferSubData = (PFNGLBUFFERSUBDATAPROC) SDL_GL_GetProcAddress("glBufferSubData");
	glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC) SDL_GL_GetProcAddress("glGetBufferSubData");
	glMapBuffer = (PFNGLMAPBUFFERPROC) SDL_GL_GetProcAddress("glMapBuffer");
	glUnmapBuffer = (PFNGLUNMAPBUFFERPROC) SDL_GL_GetProcAddress("glUnmapBuffer");
	glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC) SDL_GL_GetProcAddress("glGetBufferParameteriv");
	glGetBufferPointeriv = (PFNGLGETBUFFERPOINTERVPROC) SDL_GL_GetProcAddress("glGetBufferPointeriv");

	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) SDL_GL_GetProcAddress("glGenVertexArrays");
	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC) SDL_GL_GetProcAddress("glDeleteVertexArrays");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) SDL_GL_GetProcAddress("glBindVertexArray");

	return true;
}

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
		case GL_STACK_OVERFLOW:
			Av::Log::log("OpenGL error: stack overflow\n");
			return true;
		case GL_STACK_UNDERFLOW:
			Av::Log::log("OpenGL error: stack underflow\n");
			return true;
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
		case GL_STACK_OVERFLOW:
			Av::Log::log("OpenGL error: stack overflow (%s)\n", loc);
			return true;
		case GL_STACK_UNDERFLOW:
			Av::Log::log("OpenGL error: stack underflow (%s)\n", loc);
			return true;
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