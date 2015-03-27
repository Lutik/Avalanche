// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

// Windows
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>

// SDL
#include "SDL.h"

// STL
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>

// JSON
#include <json/json.h>

// OpenGL
//#include <GL/GL.h>
//#include "GL/glcorearb.h"
//#include "GL/glext.h"
//#include "GL/wglext.h"
#include "GL/gl_core_3_3.h"
#include "OpenGL.h"