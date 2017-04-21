#pragma once

#include <GL/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#define BUFFER_OFFSET(expr) ((char*)NULL + (expr)) 

void ENGINE_SHARED checkForGlError();
