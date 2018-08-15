//gr_particle_force.h

//TODO(zhong) : 1.添加粒子作用力注册表的局部粒子添加作用力功能
//				2.添加作用力删除功能

#ifndef _GRID_PARTICLE_FORCE_H_
#define _GRID_PARTICLE_FORCE_H_

#include"gr_particle.h"
#include<map>
#include<set>

namespace grid
{
	//class force
	class ParticleForce
	{
	public:
		virtual Vector operator()(Particle* particle) = 0;
	}; //class force

	//class Gravity
	class Gravity :
		public ParticleForce
	{
	public:

		Gravity() : g_(0.0, -9.80665) {}

		Gravity(const Vector& g) : g_(g) {}

		Gravity& set_g(const Vector& g)
		{
			g_ = g;
			return *this;
		}

		Vector get_g() const
		{
			return g_;
		}

		virtual Vector operator()(Particle* particle) override
		{
			return g_ * (1.0 / particle->get_inverse_mass());		
		}

	private:

		Vector g_;
	}; //class Gravity

	//class KeyForce
	class KeyForce :
		public ParticleForce
	{
	public:
		virtual Vector operator()(Particle* particle) override;
	}; //class KeyForce

	//使得每个粒子都可以独自进行作用力的计算
	class ParticleForceGenerator
	{
	public:

		ParticleForceGenerator(Real update_delta_time) :
			update_delta_time_(update_delta_time) {}

		ParticleForceGenerator& set_update_delta_time(Real update_delta_time)
		{
			update_delta_time_ = update_delta_time;
			return *this;
		}

		Real get_update_delta_time() const
		{
			return update_delta_time_;
		}

		void update(Particle* particle,const Vector& force)
		{
			particle->set_velocity(
				particle->get_velocity() + force * (update_delta_time_ * particle->get_inverse_mass())
			);
			particle->set_position(
				particle->get_position() + particle->get_velocity() * update_delta_time_
			);
		}

	private:

		Real update_delta_time_;

	}; //class ParticleForce

	//进行粒子和作用力的注册
	//用来保存资源
	class ParticleForceRegistry
	{
	public:

		ParticleForceRegistry();

		~ParticleForceRegistry();

		ParticleForceRegistry(const ParticleForceRegistry&) = delete;

		ParticleForceRegistry& operator=(const ParticleForceRegistry&) = delete;

		//注册全局作用力
		void register_global_force(ParticleForce* global_particle_force);

		//注册单个粒子的作用力
		void register_force(Particle* particle, ParticleForce* particle_force);

		//获得全局作用力
		Vector get_global_force(Particle* particle);

		//获得作用力注册表
		std::multimap<Particle*, ParticleForce*> get_force_registry()
		{
			return particle_force_registry_;
		}

	private:

		//全局作用力
		ParticleForce * global_force_;

		//针对于每一个粒子的局部作用力
		std::multimap<Particle*, ParticleForce*> particle_force_registry_;
	
	}; //class ParticleForceRegistry

} //namespace grid

#endif //_GRID_PARTICLE_FORCE_H_