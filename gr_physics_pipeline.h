//gr_physici_pipeline.h
//TODO(zhong) : ����Ҫģ��һ������ ��������˵ Ӧ�þ������¼���
//				1.׼����Դ ����ע���done

//TODO(zhong) : ���˿���ÿһ��������ʱ������ ��Ҫ���������ٶ� ��ÿ�����������һ��

//TODO(zhong) : ��ϸ����ע�����Ĺ�����ʽ ��ȷ�Ĺ�����ʽӦ�����ⲿ������Դ ͨ��һ���󶨶���
//				�󶨵����� Ϊ�˲������� �ɹ��߽ӹ���Դ ���ƶ� ���ⲿ�������Ի����Դָ��
//				����һ���˳����Դ ʹ������

#ifndef _GRID_PHYSICS_PIPELINE_H_
#define _GRID_PHYSICS_PIPELINE_H_

#include"gr_particle_collision.h"
#include"gr_particle_constraint.h"
#include"gr_particle_force.h"
#include"gr_particle_registry.h"
#include"gr_clocker.h"

namespace grid
{
	//class PhysicsPipeline
	class PyhsicsPipeline
	{
	public:

		PyhsicsPipeline():
			calculate_precision_(0.01666667),
			calculate_speed_(calculate_precision_),
			force_generator_(calculate_precision_),
			speed_ticker_(calculate_speed_),
			particle_registry_(nullptr),
			force_registry_(nullptr) {}

		PyhsicsPipeline(
			Real calculate_precision,
			Real calculate_speed,
			ParticleRegistry* particle_registry,
			ParticleForceRegistry* force_registry);

		PyhsicsPipeline& set_calculate_precision(
			Real calculate_precision
		) {	//��ָ�����¾���Ϊ0.0ʱ ʵ���ϲ������� �൱��ֹͣ����
			assert(calculate_precision >= 0.0);
			calculate_precision_ = calculate_precision;
			force_generator_.set_update_delta_time(calculate_precision);
			return *this;
		}

		Real get_calculate_precision() const
		{
			return calculate_precision_;
		}

		PyhsicsPipeline& set_calculate_speed(
			Real calculate_speed
		) {	//��ָ�������ٶ�Ϊ0.0ʱ �൱�ڲ������ٶ�
			assert(calculate_speed >= 0.0);
			calculate_speed_ = calculate_speed;
			speed_ticker_.set_tick(calculate_speed_);
			return *this;
		}

		Real get_calculate_speed() const
		{
			return calculate_speed_;
		}

		//����Ҫ������е�������Ϣ
		//���һ������ָ���б���
		std::set<Particle*> get_particle_resource()
		{
			return particle_registry_->get_particles();
		}

		//���ⲿ������ԴȻ�����ӹ���Դ
		void bind_particle_registry(
			ParticleRegistry& particle_registry
		) {
			particle_registry_ = &particle_registry;
		}

		void bind_force_registry(
			ParticleForceRegistry& force_registry
		) {
			force_registry_ = &force_registry;
		}

		//Ŀǰʹ������ע����ȫ��������ע�����и��¼���
		void calculate();

	private:

		//���㾫��
		Real calculate_precision_;

		//�����ٶ�
		Real calculate_speed_;

		//������������
		ParticleForceGenerator force_generator_;

		//�����ٶ��õ�ticker
		Ticker speed_ticker_;

		//����������Ҫ���µ����ӵ�
		//��Ȼ�Ҳ�Ӧ������ͨ�����ݽṹ��������
		//��Ӧ�������Լ�д���Ĳ��������泡������
		//��Ȼ������ݽṹ�Ҳ�û��ʵ�� ����
		//Quadtree* world;

		//��ô�Ҽٶ����ע����������һ֡��������Ҫ���еļ���
		//Register object_register;
		ParticleRegistry* particle_registry_;

		//����������ע����
		//ʹ�ø÷����������ӽ��и���
		ParticleForceRegistry* force_registry_;

	}; //class PhysiciPipeline

} //namespace grid

#endif //_GRID_PHYSICS_PIPELINE_H_