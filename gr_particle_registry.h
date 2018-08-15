//gr_particle_register.h

//TODO(zhong) : ���������ƶ�����
//TODO(zhong) : Ϊ�ҵ�ע����Ѱ��һ�ֺ��ʵĴ洢�ṹ

#ifndef _GRID_PARTICLE_REGISTRY_H_
#define _GRID_PARTICLE_REGISTRY_H_

#include"gr_particle.h"
#include<set>

namespace grid
{
	//manage particle resource
	//only have this copy.have all rights.
	class ParticleRegistry
	{
	public:

		ParticleRegistry(const ParticleRegistry&) = delete;
		ParticleRegistry& operator=(
			const ParticleRegistry&) = delete;

		ParticleRegistry();

		~ParticleRegistry();

		void register_particle(Particle* particle);

		bool unregister_particle(Particle* particle_ptr);

		//�����Ҿ����ṩ�����ӿ�
		//�����������Ҳ����һ������֮�� �һ��ǿ��ǿ�����Ԫ??
		//һ����˵ ����Ҫ��Դ��ʵ��Ҳֻ����Ҫ���� ��û��������˼
		//����ʱ�򷵻�һ������ ���ж����
		std::set<Particle*> get_particles()
		{
			return particles;
		}

	private:

		//������ʲô������������???
		std::set<Particle*> particles;
	}; //class ParticleRegistry

} //namespace grid

#endif //_GRID_PARTICLE_REGISTRY_H_