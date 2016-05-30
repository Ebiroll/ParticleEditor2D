#pragma once
#include "rt_core.h"
#include "particle_fx.h"

#include <memory>

namespace vis
{

    std::shared_ptr<Particle_fx_resource> load_pfx_resource(const char* file);


    struct Particle_fx_manager
	{
		void init();
		void shutdown();



        std::shared_ptr<Particle_fx_resource> create_particle_fx_resource(const Hash_key& id, uint8_t *data, uint32_t size);

        Particle_fx* create_particle_fx(const Hash_key& id, const Matrix44_f& tm);
		void destroy_particle_fx(Particle_fx* pfx);



		void update();
		void update_rendering();
	};
}
