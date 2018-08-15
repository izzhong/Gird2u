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

	//��ʵ ����Ժ�Ҫ�Ż��Ļ�
	//����ǿ���û���������ÿһ������
	//�����Ͳ������ܶ��ж� �˷�ʱ��
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
					//���ȶ��������Ӹ���ȫ��������
					for (auto particle_ptr : particles)
					{					
						force_generator_.update(
							particle_ptr, 
							force_registry_->get_global_force(particle_ptr)
						);
					}
					//Ȼ��Ӧ�þֲ�������
					//�����Ե���Щ����
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