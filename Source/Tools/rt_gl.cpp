#include <vector>
#include "rt_gl.h"
#include <cstring>

namespace vis
{
	GLuint create_shader(GLenum type, const char *src)
	{
        //TRACE("shader src: %s\n", src);
		GLuint shader = glCreateShader(type);
		GLint len = strlen(src);
		glShaderSource(shader, 1, &src, &len);
		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

		if (!status) {
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
			std::vector<char> log(len + 1);
			glGetShaderInfoLog(shader, len + 1, &len, &log[0]);
			glDeleteShader(shader);
			shader = 0;
            //TRACE("Failed to compile shader:\n%s", &log[0]);
		}

		return shader;
	}


	GLuint gl_create_program(GLenum types[], const char *source[], GLuint count)
	{
		GLuint prog = glCreateProgram();
		GLenum err;
		err = glGetError();
		printf(" err return: %d \n", err); 

		for (GLuint i = 0; i < count; ++i) {
			GLuint shader = create_shader(types[i], source[i]);
			if (shader) {
				glAttachShader(prog, shader);
			}
		}
		return prog;
	}

	void gl_link_program(GLuint prog)
	{
		glLinkProgram(prog);

		GLint status;
		glGetProgramiv(prog, GL_LINK_STATUS, &status);

		if (!status) {
			GLsizei len;
			glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
			std::vector<char> log(len + 1);
			glGetProgramInfoLog(prog, len, &len, &log[0]);
			glDeleteProgram(prog);
            //TRACE("Failed to link program:\n%s", &log[0]);
		}
		else {
			GLint count;
			GLuint shaders[8];
			glGetAttachedShaders(prog, 6, &count, shaders);
			for (int i = 0; i < count; ++i) {
				glDetachShader(prog, shaders[i]);
				glDeleteShader(shaders[i]);
			}
		}
	}

	void gl_check_program_link_status(GLuint prog)
	{
		GLint status = GL_FALSE;
		glGetProgramiv(prog, GL_LINK_STATUS, &status);

		if (status == GL_TRUE) { return; }

		GLsizei len = 0;
		glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
		std::vector<char> log(len + 1);
		glGetProgramInfoLog(prog, len, &len, &log[0]);
		glDeleteProgram(prog);
        //TRACE("Failed to link program:\n%s", &log[0]);
	}
}
