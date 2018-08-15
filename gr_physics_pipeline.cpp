//gr_physics_pipeline.cpp

#include"include/gr_physics_pipeline.h"

namespace grid
{
	PyhsicsPipeline::PyhsicsPipeline(
		Real calculate_precision,
		Real calculate_speed,
		ParticleRegistry* particle_registry,
		ParticleForceRegistry* force_registry
	) :
		calculate_precision_(calculate_precision),
		calculate_speed_(calculate_speed),
		particle_registry_(particle_registry),
		force_registry_(force_registry),
		force_generator_(calculate_precision_),
		speed_ticker_(calculate_speed_)
	{
		assert(particle_registry_);
		assert(force_registry_);
	}

	//其实 如果以后要优化的话
	//可以强制用户必须填满每一个流程
	//这样就不用做很多判断 浪费时间
	void PyhsicsPipeline::calculate()
	{
		if (speed_ticker_.get_state() == ClockerState::UNSTART)
			speed_ticker_.start();
		if (speed_ticker_.tick())
		{
			if (particle_registry_)
			{		
				auto particles = particle_registry_->get_particles();
				if (force_registry_)
				{					
					//首先对所有粒子更新全局作用力
					for (auto particle_ptr : particles)
					{					
						force_generator_.update(
							particle_ptr, 
							force_registry_->get_global_force(particle_ptr)
						);
					}
					//然后应用局部作用力
					//这里显得有些啰嗦
					auto force_registry = force_registry_->get_force_registry();
					for (auto it : force_registry)
					{
						force_generator_.update(
							it.first,
							(*it.second)(it.first)
						);
					}
				}
			}
		}	
	}

} //namespace grid