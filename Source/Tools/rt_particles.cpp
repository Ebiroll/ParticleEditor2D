
#if 0
#include "glsl.h"
#include "core/trace.h"
#include "core/math.h"
#include "core/time.h"
#include "core/random.h"
#endif

//#include "engine.h"
//#include "texture.h"
#define  GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glext.h>
#include <QGLFunctions>
#include "particle_fx.h"
#include "glsl.h"

#include "rt_particles.h"
#include "rt_gl.h"
namespace vis
{
    RT_particles::RT_particles()
    {
        const char* vs = GLSL_SRC(

        struct Particle
        {
            vec3 pos;
            float rot;
            float size;
            float anim;
            uint color;
        };

        layout(std430, binding = 0) buffer P_data
        {
            Particle p_data[];
        };

        uniform mat4 rotation;
        uniform mat4 view_proj;
        uniform vec2 anim_params;

        uniform vec2 vc[4] = vec2[](vec2(0, 0), vec2(0, 1), vec2(1, 1), vec2(1, 0));

        out gl_PerVertex
        {
            vec4 gl_Position;
        };

        out vec2 uv;
        out vec4 color;

        vec2 rotate(vec2 p, float a)
        {
            float s = sin(a);
            float c = cos(a);
            return vec2(p.x * c - p.y * s, p.x * s + p.y * c);
        }

        void main()
        {
            vec4 pcolor = unpackUnorm4x8(p_data[gl_InstanceID].color);
            float anim = floor(p_data[gl_InstanceID].anim + 0.5) * anim_params.x;
            vec2 uv_anim;
            uv_anim.x = fract(anim);
            uv_anim.y = anim_params.y * (anim - uv_anim.x);

            uv = uv_anim + vc[gl_VertexID] * anim_params;

            vec2 pos = (2.0 * vc[gl_VertexID] - 1.0) * p_data[gl_InstanceID].size;
            pos = rotate(pos, p_data[gl_InstanceID].rot);
            gl_Position = rotation * vec4(pos.xy, 0.0, 1.0);
            gl_Position.xyz += p_data[gl_InstanceID].pos.xyz;
            gl_Position = view_proj * gl_Position;
            color = pcolor;
        });

        const char* fs = GLSL_SRC(

            in vec2 uv;
            in vec4 color;

            layout(binding = 0) uniform sampler2D tex;

            layout(location = 0) out vec4 frag;

        void main()
        {
            vec4 c = texture(tex, uv);
            frag = c * color;
        });

        _vs_prog = gl_create_shader_program(GL_VERTEX_SHADER, vs);
        _fs_prog = gl_create_shader_program(GL_FRAGMENT_SHADER, fs);

        gl_check_program_link_status(_vs_prog);
        gl_check_program_link_status(_fs_prog);

        //glGenProgramPipelines(1, &_pipeline);
        //glUseProgramStages(_pipeline, GL_VERTEX_SHADER_BIT, _vs_prog);
        //glUseProgramStages(_pipeline, GL_FRAGMENT_SHADER_BIT, _fs_prog);

        _u_rotation = glGetUniformLocation(_vs_prog, "rotation");
        _u_view_proj = glGetUniformLocation(_vs_prog, "view_proj");
        _u_anim_params = glGetUniformLocation(_vs_prog, "anim_params");

        glGenSamplers(1, &_sampler);
        glSamplerParameteri(_sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glSamplerParameteri(_sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glSamplerParameteri(_sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glSamplerParameteri(_sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        //glCreateBuffers(1, &_sb);
        //glNamedBufferData(_sb, sizeof(VS_particle) * 1000, 0, GL_STREAM_DRAW);

        glGenVertexArrays(1, &_va);
    }

    RT_particles::~RT_particles()
    {
        glDeleteBuffers(1, &_sb);
        glDeleteSamplers(1, &_sampler);
        //glDeleteProgramPipelines(1, &_pipeline);
        glDeleteProgram(_vs_prog);
        glDeleteProgram(_fs_prog);
    }

    void RT_particles::setup(Render_context* rc)
    {
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glDepthMask(GL_FALSE);

        glUseProgram(0);
        //glBindProgramPipeline(_pipeline);

        glBindSampler(0, _sampler);
        //glBindSampler(0, 0);
    }

    inline uint32_t pack_color(const float c[4])
    {
        uint32_t r = uint32_t(c[0] * 255.0f);
        uint32_t g = uint32_t(c[1] * 255.0f) << 8;
        uint32_t b = uint32_t(c[2] * 255.0f) << 16;
        uint32_t a = uint32_t(c[3] * 255.0f) << 24;
        return r | g | b | a;
    }
    void RT_particles::draw(Render_context* rc, Render_element* elem, Render_data* rd)
    {
        RE_particles* re_particles = (RE_particles*)elem;

        Matrix44_f mat = rc->view_transform;
        mat[3] = Vector4_f(0, 0, 0, 1.0f);

        //glProgramUniformMatrix4fv(_vs_prog, _u_rotation, 1, GL_FALSE, &mat[0][0]);
        //glProgramUniformMatrix4fv(_vs_prog, _u_view_proj, 1, GL_FALSE, &rc->view_proj[0][0]);

        const Particle_fx* ps = (Particle_fx*)rd->meta_data;
        const Particle_fx::Emitter& em = ps->emitters[re_particles->emitter_index];

        float anim_params[2] = { 1.0f / em.anim_x, 1.0f / em.anim_y};
        //glProgramUniform2fv(_vs_prog, _u_anim_params, 1, &anim_params[0]);

        uint32_t n_particles = em.active_particles;
        const Particle* particles = em.particles;

        VS_particle vs_particles[1000];
        for (uint32_t i = 0; i < n_particles; ++i) {
            const Particle& p = particles[i];
            VS_particle& vp = vs_particles[i];
            vp.pos[0] = p.position[0];
            vp.pos[1] = p.position[1];
            vp.pos[2] = p.position[2];
            vp.rot = p.rotation;
            vp.size = p.size;
            vp.anim = p.animation;
            vp.color = pack_color(p.color);
        }

        //glBindBuffer(GL_SHADER_STORAGE_BUFFER, _sb);
        //glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(VS_particle)* n_particles, &vs_particles[0]);
        //glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

        //glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, _sb);

        //glBindMultiTextureEXT(GL_TEXTURE0, GL_TEXTURE_2D, em.texture->texture_id());

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // old glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        glBindVertexArray(_va);
        glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, n_particles);
        glBindVertexArray(0);

        ++rc->draw_calls;
    }

    Render_element* RT_particles::alloc_element()
    {
        RE_particles* elem = new RE_particles;
        elem->type_index = 1; // RT_PARTICLES;
        return elem;
    }

    void RT_particles::free_element(Render_element* elem)
    {
        RE_particles* re_particles = (RE_particles*)elem;
        delete re_particles;
    }

    void RT_particles::init_element(Render_element* elem, Memory_stream* s)
    {
        RE_particles* re_particles = (RE_particles*)elem;
        re_particles->type_index = 1; //RT_PARTICLES;
    }

    Render_element* RT_particles::create_element(Memory_stream*)
    {
        Render_element* elem = alloc_element();
        init_element(elem, 0);
        return elem;
    }

    void RT_particles::destroy_element(Render_element* elem)
    {
        RE_particles* re_particles = (RE_particles*)elem;
        free_element(elem);
    }
}
