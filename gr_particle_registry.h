//gr_particle_register.h

//TODO(zhong) : 定义合理的移动操作
//TODO(zhong) : 为我的注册器寻找一种合适的存储结构

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

		//所以我决定提供容器接口
		//但是这个东西也不是一个长久之计 我还是考虑考虑友元??
		//一般来说 我想要资源其实我也只是想要遍历 并没有其他意思
		//这种时候返回一个数组 该有多棒啊
		std::set<Particle*> get_particles()
		{
			return particles;
		}

	private:

		//到底用什么容器来保存呢???
		std::set<Particle*> particles;
	}; //class ParticleRegistry

} //namespace grid

#endif //_GRID_PARTICLE_REGISTRY_H_