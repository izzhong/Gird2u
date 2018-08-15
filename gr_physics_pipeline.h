//gr_physici_pipeline.h
//TODO(zhong) : 我想要模拟一个场景 按道理来说 应该经过如下几步
//				1.准备资源 粒子注册表done

//TODO(zhong) : 除了控制每一步的运算时间间隔外 还要控制运算速度 即每隔多少秒计算一次

//TODO(zhong) : 仔细调整注册器的工作方式 正确的工作方式应该是外部整理资源 通过一个绑定动作
//				绑定到管线 为了不出错误 由管线接管资源 即移动 对外部仅仅可以获得资源指针
//				对于一般的顺序资源 使用数组

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
		) {	//当指定更新精度为0.0时 实际上并不更新 相当于停止更新
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
		) {	//当指定更新速度为0.0时 相当于不限制速度
			assert(calculate_speed >= 0.0);
			calculate_speed_ = calculate_speed;
			speed_ticker_.set_tick(calculate_speed_);
			return *this;
		}

		Real get_calculate_speed() const
		{
			return calculate_speed_;
		}

		//我需要获得所有的粒子信息
		//获得一个粒子指针列表即可
		std::set<Particle*> get_particle_resource()
		{
			return particle_registry_->get_particles();
		}

		//由外部分配资源然后该类接管资源
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

		//目前使用粒子注册表和全局作用力注册表进行更新计算
		void calculate();

	private:

		//计算精度
		Real calculate_precision_;

		//计算速度
		Real calculate_speed_;

		//作用力发生器
		ParticleForceGenerator force_generator_;

		//控制速度用的ticker
		Ticker speed_ticker_;

		//保存所有需要更新地粒子地
		//显然我不应该用普通的数据结构保存粒子
		//我应该用我自己写的四叉树来保存场景粒子
		//当然这个数据结构我并没有实现 哈哈
		//Quadtree* world;

		//那么我假定这个注册表包含了这一帧中所有需要进行的计算
		//Register object_register;
		ParticleRegistry* particle_registry_;

		//粒子作用力注册器
		//使用该发生器对粒子进行更新
		ParticleForceRegistry* force_registry_;

	}; //class PhysiciPipeline

} //namespace grid

#endif //_GRID_PHYSICS_PIPELINE_H_