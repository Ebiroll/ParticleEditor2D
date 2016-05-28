#pragma once

#define GLSL_VER "#version 440\n"
#define GLSL_SRC(src) #src
#define GLSL_SRC44(src) "#version 440\n" #src

//#define GLSL44(src) "#version 440\n" #src

namespace vis
{
	extern const char* vs_incl;
	extern const char* fs_incl;
}
