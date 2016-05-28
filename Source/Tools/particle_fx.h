#pragma once

#include <stdint.h>
#include <vector>

#if 0
#include "core/types.h"
#include "core/vector.h"
#include "core/random.h"
#include "core/vsd.h"

#include "engine/graphics.h"
#include "engine/texture.h"
#endif

#include "rt_core.h"

#include <memory>

namespace vis
{
	struct Particle
	{
		float position[3];
		float rotation;
		float velocity[3];
		float rotation_velocity;
		float color[4];
		float size;
		float animation;
		float time;
		float time_factor;
	};

	enum
	{
		PARTICLE_AFFECTOR_SIZE,
		PARTICLE_AFFECTOR_COLOR,
		PARTICLE_AFFECTOR_ANIMATION,
		PARTICLE_AFFECTOR_FORCE,
		PARTICLE_AFFECTOR_FRICTION,
	};

	struct Particle_affector
	{
		union
		{
			struct
			{
				float factor;
			} size;
			struct
			{
				float factor[4];
			} color;
			struct
			{
				uint16_t start, end, fps;
				uint16_t loop : 1;
			} animation;
			struct
			{
				float factor[3];
			} force;
			struct
			{
				float factor;
			} friction;
		};
		
		uint16_t id;
		uint16_t type;
		float time[2];
	};

	enum
	{
		EMITTER_TYPE_BOX,
		EMITTER_TYPE_SPHERE,
		EMITTER_TYPE_CYLINDER,
	};

	struct Emitter_data
	{
		float x_angle;
		float x_angle_spread;
		float y_angle;
		float y_angle_spread;
		float speed;
		float speed_spread;
		float rotation;
		float rotation_spread;
		float rotation_speed;
		float rotation_speed_spread;
		float size;
		float size_spread;
		float duration;
		float duration_spread;
		float color[4];
		float emissive;
		float emit_rate;
		uint16_t anim;
		uint16_t anim_spread;
		uint16_t anim_x;
		uint16_t anim_y;
		
		uint16_t id;
		uint16_t emitter_type;
		float emitter_size[3];

		uint16_t max_particles;
		uint16_t num_affectors;

        //std::shared_ptr<Texture> texture;
	};

    struct Particle_fx_resource
	{
		Particle_fx_resource();
		virtual ~Particle_fx_resource() {}

        //void read(const VSD_container&);
        //void read_emitter(const VSD_container&, Emitter_data&);
        //void read_affector(const VSD_container&, Particle_affector&);

		uint32_t total_particles;
		std::vector<Emitter_data> emitters;
		std::vector<Particle_affector> affectors;
	};

	struct Particle_fx
	{
		struct Emitter : Emitter_data
		{
			float emit_time;
			uint32_t active_particles;
			Particle* particles;
			Particle_affector* affectors;
		};

		Particle_fx(std::shared_ptr<Particle_fx_resource>& res);
        ~Particle_fx();

		uint32_t num_emitters;
		std::unique_ptr<Emitter[]> emitters;
		std::unique_ptr<Particle[]> particles;
		std::unique_ptr<Particle_affector[]> affectors;
		
        Render_data _rdata;
		std::shared_ptr<Particle_fx_resource> resource;

		void update(float dt);
		void update_emitter(Emitter& em, float dt);
		void apply_affector(Emitter& em, Particle_affector&pf, float dt);
		void emit_particle(Emitter& em);
	};
}
