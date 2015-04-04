#ifndef _AVALANCHE_OPENGL_H_
#define _AVALANCHE_OPENGL_H_

//OpenGL debug and error handling
bool CheckGLError();
bool CheckGLError(char *loc);
void ProgramLog(GLuint program);
void ShaderLog(GLuint shader);

#endif