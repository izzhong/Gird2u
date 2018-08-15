//gr_particle_regitry.cpp

#include"include/gr_particle_registry.h"

namespace grid
{
	ParticleRegistry::ParticleRegistry() :
		particles() {}

	void ParticleRegistry::register_particle(
		Particle* particle)
	{
		assert(particle);
		particles.insert(particle);
	}

	bool ParticleRegistry::unregister_particle(Particle* particle_ptr)
	{
		auto it = particles.find(particle_ptr);
		if (it == particles.end())
		{
			return false;
		}
		else
		{
			particles.erase(it);
			return true;
		}
	}

	ParticleRegistry::~ParticleRegistry()
	{
	}

} //namespce grid