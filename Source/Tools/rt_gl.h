#pragma once

#include <array>

#define  GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
//#define GL_GLEXT_PROTOTYPES 1
//#include <GL/glext.h>

#include <QGLFunctions>


#include "glsl.h"

namespace vis
{
	GLuint gl_create_program(GLenum types[], const char *source[], GLuint count);
	void gl_link_program(GLuint prog);

	template<typename... T>
	GLuint gl_create_shader_program(GLenum type, T... args)
	{
		std::array<const char*, 1 + sizeof...(T)> x{ { GLSL_VER, args... } };
        //return glCreateShaderProgramv(type, x.size(), &x[0]);
        return 1;
	}

	void gl_check_program_link_status(GLuint prog);
}
