#pragma once

#include "rt_core.h"
#include <stdint.h>
#include <cstdint>
namespace vis
{


	struct RE_particles : Render_element
	{
		uint32_t emitter_index;
	};

    struct RT_particles
	{
		RT_particles();
		virtual ~RT_particles();

		void setup(Render_context* rc);
		void draw(Render_context* rc, Render_element* elem, Render_data* data);

		Render_element* alloc_element();
		void free_element(Render_element* elem);

        void init_element(Render_element* e, Memory_stream*);

		Render_element* create_element(Memory_stream*);
		void destroy_element(Render_element* e);

		struct VS_particle
		{
			float pos[3];
			float rot;
			float size;
			float anim;
			uint32_t color;
			float pad[1];
		};

	private:

		GLint _u_rotation;
		GLint _u_view_proj;
		GLint _u_anim_params;
		GLuint _va;
		GLuint _sb;
		GLuint _sampler;
		GLuint _vs_prog;
		GLuint _fs_prog;
		GLuint _pipeline;
	};
}
