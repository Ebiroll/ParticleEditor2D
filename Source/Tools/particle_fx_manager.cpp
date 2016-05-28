
#if 0
#include "core/vsd_util.h"
#include "engine/engine.h"
#include "engine/rt_particles.h"
#endif

#include "particle_fx.h"
#include "particle_fx_manager.h"
#include "rt_particles.h"
#include <memory>
#include <vector>
#include "inttypes.h"
#include "rt_types.h"

namespace vis
{


        struct Context
        {

            typedef std::pair<uint32_t, std::weak_ptr<Particle_fx_resource>> Entry;

			std::vector<Entry> _resource_table;
			
            //std::vector<std::shared_ptr<Texture>> _stored_textures;
            //std::vector<std::shared_ptr<Particle_fx_resource>> _stored_resources;

			std::vector<Particle_fx*> _instances;

			uint32_t _added_render_elements;
			std::vector<RE_particles*> _render_elements;

			std::shared_ptr<Particle_fx> _test;
			
			void init()
			{
				// preload textures
                //_stored_textures.push_back(engine::texture_manager->load_texture("fire.dds"));
                //_stored_textures.push_back(engine::texture_manager->load_texture("explosion.dds"));

				// preload resources
                //_stored_resources.push_back(load_pfx_resource("acft_smoke1.pfx"));
			}

			void update()
			{
                //float dt = engine::frame_time;
                float dt = 0.0f;
				for (uint32_t i = 0; i < _instances.size(); ++i) {
					_instances[i]->update(dt);
				}
			}

			void update_rendering()
			{
				_added_render_elements = 0;
				for (uint32_t i = 0; i < _instances.size(); ++i) {
					render_pfx(_instances[i]);
				}
			}

			void render_pfx(Particle_fx* pfx)
			{
				for (uint32_t i = 0; i < pfx->num_emitters; ++i) {
					if (_render_elements.size() < _added_render_elements + 1) {
                        //_render_elements.push_back((RE_particles*)engine::graphics->fetch_type(RT_PARTICLES)->create_element());
					}
					RE_particles* re = _render_elements[_added_render_elements++];
					re->emitter_index = i;
                    //engine::graphics->fetch_pass(RP_PARTICLES)->add_instance(re, &pfx->_rdata);
				}
			}

			std::vector<Entry>::iterator find_pfx(uint32_t hash)
			{
				auto lb = [](const Entry& e, uint32_t h){ return h < e.first; };
				return std::lower_bound(_resource_table.begin(), _resource_table.end(), hash, lb);
			}

#if 0
            std::shared_ptr<Particle_fx_resource> create_pfx_resource(const Hash_key& id, uint8_t *data, uint32_t data_size)
            {
				auto it = find_pfx(id);

				if (it != _resource_table.end() && it->first == id && !it->second.expired()) {
					return (it)->second.lock();
				}

				std::shared_ptr<Particle_fx_resource> new_pfx(new Particle_fx_resource());

				VSD_container vc;
				read_vsd_container((char*)(&data[0]), vc);
				new_pfx->read(vc);

				if (it != _resource_table.end() && it->first == id) {
					it->second = new_pfx;
				}
				else {
					_resource_table.insert(it, std::make_pair(id, new_pfx));
				}

				return new_pfx;
			}
			std::shared_ptr<Particle_fx_resource> load_pfx_resource(const char* file)
			{
				FILE *fp = fopen(file, "rb");
				fseek(fp, 0, SEEK_END);
				uint32_t size = ftell(fp);
				fseek(fp, 0, SEEK_SET);
				std::vector<uint8_t> data;
				data.resize(size + 1);
				fread(&data[0], size, 1, fp);
				fclose(fp);
				data.back() = 0;
                //return create_pfx_resource(file, &data[0], data.size());
			}

			Particle_fx* create_pfx(const Hash_key& id, const Matrix44_f& tm)
			{
				auto it = find_pfx(id);

				if (it != _resource_table.end()) {
				  std::shared_ptr<Particle_fx_resource> pfr = it->second.lock();
					_instances.push_back(new Particle_fx(pfr));
					_instances.back()->_rdata.matrix[0] = translation(Vector3_f(0, 2.0f, 0));
					return _instances.back();
				}
				return 0;
			}

			void destroy_pfx(Particle_fx* pfx)
			{

			}
#endif
        };

		static Context context;

		inline float rand_range(float min, float max)
		{
            //return rand_f(min, max, seed);
		}

		inline float rand_spread(float spread)
		{
            //return rand_range(-spread, spread);
		}
#if 0
    Particle_fx_resource::Particle_fx_resource()
	{
		total_particles = 0;
	}

	void Particle_fx_resource::read(const VSD_container& vc)
	{
		ASSERT(emitters.empty());

		total_particles = 0;

		for (auto it = vc.begin(); it != vc.end(); ++it) {
			ASSERT(it.type() == VSD_CONTAINER);
			emitters.resize(emitters.size() + 1);
            read_emitter(it.container(), emitters.back());
		}
	}

	void Particle_fx_resource::read_emitter(const VSD_container& vc, Emitter_data& e)
	{
		e.x_angle = vc.value("x_angle");
		e.x_angle_spread = vc.value("x_angle_spread");
		e.y_angle = vc.value("y_angle");
		e.y_angle_spread = vc.value("y_angle_spread");
		e.speed = vc.value("speed");
		e.speed_spread = vc.value("speed_spread");
		e.rotation = vc.value("rotation");
		e.rotation_spread = vc.value("rotation_spread");
		e.rotation_speed = vc.value("rotation_speed");
		e.rotation_speed_spread = vc.value("rotation_speed_spread");
		e.size = vc.value("size");
		e.size_spread = vc.value("size_spread");
		e.duration = vc.value("duration");
		e.duration_spread = vc.value("duration_spread");
		e.emit_rate = vc.value("emit_rate");
		e.anim = (int)vc.value("animation");
		e.anim_spread = (int)vc.value("animation_spread");
		e.anim_x = (int)vc.value("animation_x");
		e.anim_y = (int)vc.value("animation_y");

		const float* color = vc.value("color");
		e.color[0] = color[0];
		e.color[1] = color[1];
		e.color[2] = color[2];
		e.color[3] = color[3];

		e.id = (int)vc.value("id");

		e.emitter_type = (int)vc.value("emitter_type");
		const float* emitter_size = vc.value("emitter_size");
		e.emitter_size[0] = emitter_size[0];
		e.emitter_size[1] = emitter_size[1];
		e.emitter_size[2] = emitter_size[2];

		e.max_particles = (int)vc.value("max_particles");
		e.texture = engine::texture_manager->fetch_texture((const char*)vc.value("texture"));
		
		e.num_affectors = 0;
		const VSD_container& affectors_vc = vc.container("affectors");
		if (&affectors_vc) {
			for (auto it = affectors_vc.begin(); it != affectors_vc.end(); ++it) {
				ASSERT(it.type() == VSD_CONTAINER);
				++e.num_affectors;
				affectors.resize(affectors.size() + 1);
				read_affector(it.container(), affectors.back());
			}
		}

		total_particles += e.max_particles;
	}

	void Particle_fx_resource::read_affector(const VSD_container& vc, Particle_affector& af)
	{
		af.id = (int)vc.value("id");
		af.type = (int)vc.value("type");
		if (!vc.value("start_time", af.time[0])) {
			af.time[0] = 0.0f;
		}
		if (!vc.value("end_time", af.time[1])) {
			af.time[1] = 1.0f;
		}
		switch (af.type) {
		case PARTICLE_AFFECTOR_SIZE:
			af.size.factor = vc.value("factor");
			break;
		case PARTICLE_AFFECTOR_COLOR:
		{
			const float* factor = vc.value("factor");
			af.color.factor[0] = factor[0];
			af.color.factor[1] = factor[1];
			af.color.factor[2] = factor[2];
			af.color.factor[3] = factor[3];
			break;
		}
		case PARTICLE_AFFECTOR_ANIMATION:
			af.animation.start = (int)vc.value("start");
			af.animation.end = (int)vc.value("end");
			af.animation.fps = (int)vc.value("fps");
			af.animation.loop = (int)vc.value("loop");
			break;
		case PARTICLE_AFFECTOR_FORCE:
		{
			const float* factor = vc.value("factor");
			af.force.factor[0] = factor[0];
			af.force.factor[1] = factor[1];
			af.force.factor[2] = factor[2];
			break;
		}
		case PARTICLE_AFFECTOR_FRICTION:
			af.friction.factor = vc.value("factor");
			break;
		}
	}

	Particle_fx::Particle_fx(std::shared_ptr<Particle_fx_resource>& res)
	{
		_rdata.meta_data = this;

		resource = res;
		num_emitters = res->emitters.size();
		emitters.reset(new Emitter[num_emitters]);
		particles.reset(new Particle[res->total_particles]);
		affectors.reset(new Particle_affector[res->affectors.size()]);

		for (uint32_t i = 0; i < res->affectors.size(); ++i) {
			affectors[i] = res->affectors[i];
		}

		uint32_t particle_offset = 0;
		uint32_t affector_offset = 0;
		for (uint32_t i = 0; i < num_emitters; ++i) {
			Emitter& e = emitters[i];
			*((Emitter_data*)&e) = res->emitters[i];
			e.emit_time = 0;
			e.active_particles = 0;
			e.particles = &particles[particle_offset];
			particle_offset += e.max_particles;
			e.affectors = &affectors[affector_offset];
			affector_offset += e.num_affectors;
		}
	}
	
	void Particle_fx_manager::init()
	{
		context.init();
		Particle_fx* ps = context.create_pfx("acft_smoke1.pfx", translation(Vector3_f(0, 2.0f, 0)));
		ps->_rdata.matrix[0] = translation(Vector3_f(0, 2.0f, 0));
	}

	void Particle_fx_manager::shutdown()
	{
	}

	std::shared_ptr<Particle_fx_resource> Particle_fx_manager::create_particle_fx_resource(const Hash_key& id, uint8_t *data, uint32_t data_size)
	{
		return context.create_pfx_resource(id, data, data_size);
	}

	Particle_fx* Particle_fx_manager::create_particle_fx(const Hash_key& id, const Matrix44_f& tm)
	{
		return context.create_pfx(id, tm);
	}

	void Particle_fx_manager::destroy_particle_fx(Particle_fx* pfx)
	{

	}
#endif
	void Particle_fx_manager::update()
	{
		//context.update();
	}

	void Particle_fx_manager::update_rendering()
	{
		//context.update_rendering();
	}

	void Particle_fx::update(float dt)
	{
		for (uint32_t i = 0; i < num_emitters; ++i) {
			update_emitter(emitters[i], dt);
		}
	}

	void Particle_fx::update_emitter(Emitter& em, float dt)
	{
		float emit_delay = 1.0f / em.emit_rate;
		em.emit_time += dt;
		while (em.emit_time > 0 && em.active_particles < em.max_particles) {
			emit_particle(em);
			em.emit_time -= emit_delay;
		}
		em.emit_time = fmod(em.emit_time, emit_delay);

		uint32_t i = 0;
		while (i < em.active_particles) {
			Particle& p = em.particles[i];
			p.time += p.time_factor * dt;
			if (p.time > 1.0f) {
				p = em.particles[--em.active_particles];
				continue;
			}
			p.position[0] += p.velocity[0] * dt;
			p.position[1] += p.velocity[1] * dt;
			p.position[2] += p.velocity[2] * dt;
			p.rotation += p.rotation_velocity * dt;

			++i;
		}

		i = 0;
		while (i < em.num_affectors) {
			apply_affector(em, em.affectors[i], dt);
			++i;
		}
	}

	void apply_size_affector(const Particle_affector& affector, Particle* particles, uint32_t count, float dt)
	{
		float f = affector.size.factor * dt;

		for (uint32_t i = 0; i < count; ++i) {
			Particle& p = particles[i];
			if (p.time >= affector.time[0] && p.time <= affector.time[1]) {
				p.size += f;
			}
		}
	}

	void apply_color_affector(const Particle_affector& affector, Particle* particles, uint32_t count, float dt)
	{
		float c[4];
		c[0] = affector.color.factor[0] * dt;
		c[1] = affector.color.factor[1] * dt;
		c[2] = affector.color.factor[2] * dt;
		c[3] = affector.color.factor[3] * dt;

		for (uint32_t i = 0; i < count; ++i) {
			Particle& p = particles[i];
			if (p.time >= affector.time[0] && p.time <= affector.time[1]) {
				p.color[0] = clamp(p.color[0] + c[0], 0.0f, 1.0f);
				p.color[1] = clamp(p.color[1] + c[1], 0.0f, 1.0f);
				p.color[2] = clamp(p.color[2] + c[2], 0.0f, 1.0f);
				p.color[3] = clamp(p.color[3] + c[3], 0.0f, 1.0f);
			}
		}
	}

	void apply_animation_affector(const Particle_affector& affector, Particle* particles, uint32_t count, float dt)
	{
		float start = affector.animation.start;
		float end = affector.animation.end;

		for (uint32_t i = 0; i < count; ++i) {
			Particle& p = particles[i];
			if (p.time >= affector.time[0] && p.time <= affector.time[1]) {
				float anim = p.animation;
				anim += (float)affector.animation.fps * dt;
				if (anim > end) {
					if (affector.animation.loop) {
						anim = clamp(anim - (end - start), start, end);
					}
					else {
						anim = end;
					}
				}
				else if (anim < start) {
					if (affector.animation.loop) {
						anim = clamp(anim + (end - start), start, end);
					}
					else {
						anim = start;
					}
				}
				p.animation = anim;
			}
		}
	}

	void apply_force_affector(const Particle_affector& affector, Particle* particles, uint32_t count, float dt)
	{
		float f[3];
		f[0] = affector.force.factor[0] * dt;
		f[1] = affector.force.factor[1] * dt;
		f[2] = affector.force.factor[2] * dt;

		for (uint32_t i = 0; i < count; ++i) {
			Particle& p = particles[i];
			if (p.time >= affector.time[0] && p.time <= affector.time[1]) {
				p.velocity[0] += f[0];
				p.velocity[1] += f[1];
				p.velocity[2] += f[2];
			}
		}
	}

	void apply_friction_affector(const Particle_affector& affector, Particle* particles, uint32_t count, float dt)
	{
		float f = min(1.0f, affector.friction.factor * dt);

		for (uint32_t i = 0; i < count; ++i) {
			Particle& p = particles[i];
			if (p.time >= affector.time[0] && p.time <= affector.time[1]) {
				p.velocity[0] -= p.velocity[0] * f;
				p.velocity[1] -= p.velocity[1] * f;
				p.velocity[2] -= p.velocity[2] * f;
			}
		}
	}

	static void(*affector_func[5])(const Particle_affector&, Particle*, uint32_t, float) =
	{
		apply_size_affector,
		apply_color_affector,
		apply_animation_affector,
		apply_force_affector, 
		apply_friction_affector
	};

	void Particle_fx::apply_affector(Emitter& em, Particle_affector& af, float dt)
	{
		affector_func[af.type](af, em.particles, em.active_particles, dt);
	}

	Vector3_f emit_cube_pos(const Particle_fx::Emitter& em)
	{
		Vector3_f v(rand_spread(0.5f), rand_spread(0.5f), rand_spread(0.5f));
		return v * Vector3_f(em.emitter_size);
	}

	Vector3_f emit_sphere_pos(const Particle_fx::Emitter& em)
	{
		Vector3_f v(rand_spread(1.0f), rand_spread(1.0f), rand_spread(1.0f));
		return normalize(v) * rand_range(em.emitter_size[0], em.emitter_size[1]);
	}

	Vector3_f emit_cylinder_pos(const Particle_fx::Emitter& em)
	{
		Vector3_f v(rand_spread(1.0f), rand_spread(1.0f), 0.0f);
		v = normalize(v);
		v.x *= rand_range(em.emitter_size[0], em.emitter_size[1]);
		v.y *= rand_range(em.emitter_size[0], em.emitter_size[1]);
		v.z = rand_spread(0.5f) * em.emitter_size[2];
		return v;
	}

	static Vector3_f (*emit_func[3])(const Particle_fx::Emitter&) =
	{
		emit_cube_pos,
		emit_sphere_pos,
		emit_cylinder_pos
	};

	void Particle_fx::emit_particle(Emitter& em)
	{
		Particle& p = em.particles[em.active_particles++];

		float speed = em.speed + rand_spread(em.speed_spread);
		float x_angle = em.x_angle + rand_spread(em.x_angle_spread);
		float y_angle = em.y_angle + rand_spread(em.y_angle_spread);
		Matrix44_f m = _rdata.matrix[0] * rotation_yaw_pitch_roll(y_angle, x_angle, 0.0f);

		p.velocity[0] = m[2][0] * speed;
		p.velocity[1] = m[2][1] * speed;
		p.velocity[2] = m[2][2] * speed;

		p.rotation_velocity = em.rotation_speed + rand_spread(em.rotation_speed_spread);

		Vector3_f pos = emit_func[em.emitter_type](em);
		
		pos = Vector3_f(_rdata.matrix[0] * Vector4_f(pos, 1.0f));

		p.position[0] = pos[0];
		p.position[1] = pos[1];
		p.position[2] = pos[2];

		p.rotation = em.rotation + rand_spread(em.rotation_spread);

		p.size = em.size + rand_spread(em.size_spread);

		p.time = 0.0f;
		p.time_factor = 1.0f / (em.duration + rand_spread(em.duration_spread));

		p.animation = em.anim + rand_range(0, em.anim_spread + 1);

		p.color[0] = em.color[0];
		p.color[1] = em.color[1];
		p.color[2] = em.color[2];
		p.color[3] = em.color[3];
	}

}
