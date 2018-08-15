//force.cpp

#include"include/gr_particle_force.h"
#include<Windows.h>

namespace grid
{
	//----------------------------------------//

	Vector KeyForce::operator()(Particle* particle)
	{
		particle;
		if (GetAsyncKeyState('A') & 0x8000)
			return Vector(-10, 0.0);
		if (GetAsyncKeyState('D') & 0x8000)
			return Vector(10, 0.0);
		if (GetAsyncKeyState('W') & 0x8000)
			return Vector(0.0, -10);
		if (GetAsyncKeyState('S') & 0x8000)
			return Vector(0.0, 10);
		return Vector();
	}

	//-----------------------------------------//

	ParticleForceRegistry::ParticleForceRegistry() :
		global_force_(nullptr),
		particle_force_registry_() {}

	ParticleForceRegistry::~ParticleForceRegistry()
	{

	}

	//注册单个粒子的作用力
	void ParticleForceRegistry::register_force(
		Particle* particle, ParticleForce* particle_force)
	{
		particle_force_registry_.insert(
			{ particle ,particle_force }
		);
	}

	void ParticleForceRegistry::register_global_force(
		ParticleForce* global_force)
	{
		assert(global_force);
		global_force_ = global_force;		
	}

	Vector ParticleForceRegistry::get_global_force(Particle* particle)
	{
		if (particle)
			return (*global_force_)(particle);
		else
			return Vector();
	}

} //namespace grid