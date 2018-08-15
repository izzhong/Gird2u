//gr_particle_force.h

//TODO(zhong) : 1.�������������ע���ľֲ������������������
//				2.���������ɾ������

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

	//ʹ��ÿ�����Ӷ����Զ��Խ����������ļ���
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

	//�������Ӻ���������ע��
	//����������Դ
	class ParticleForceRegistry
	{
	public:

		ParticleForceRegistry();

		~ParticleForceRegistry();

		ParticleForceRegistry(const ParticleForceRegistry&) = delete;

		ParticleForceRegistry& operator=(const ParticleForceRegistry&) = delete;

		//ע��ȫ��������
		void register_global_force(ParticleForce* global_particle_force);

		//ע�ᵥ�����ӵ�������
		void register_force(Particle* particle, ParticleForce* particle_force);

		//���ȫ��������
		Vector get_global_force(Particle* particle);

		//���������ע���
		std::multimap<Particle*, ParticleForce*> get_force_registry()
		{
			return particle_force_registry_;
		}

	private:

		//ȫ��������
		ParticleForce * global_force_;

		//�����ÿһ�����ӵľֲ�������
		std::multimap<Particle*, ParticleForce*> particle_force_registry_;
	
	}; //class ParticleForceRegistry

} //namespace grid

#endif //_GRID_PARTICLE_FORCE_H_