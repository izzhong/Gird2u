//gr_particle_collision.h

#ifndef _GRID_PARTICLE_COLLISION_H_
#define _GRID_PARTICLE_COLLISION_H_

#include"gr_particle.h"

namespace grid
{
	//get the pair of the particle.calculate the particle collision result.
	struct ParticleCollisionResult
	{
		Particle* particle[2];

		Vector collision_position;

		Vector collision_normal;

		Real collision_depth;
	};

	//判断两个质点是否碰撞
	class ParticleCollisionDetection
	{
	public:

		ParticleCollisionDetection(Real detection_precision = 1.0) :
			detection_precision_(detection_precision) {}

		ParticleCollisionDetection& set_detection_precision(
			Real detection_precition
		) {
			detection_precision_ = detection_precition;
		}

		Real get_detection_precison() const
		{
			return detection_precision_;
		}

		bool operator()(
			Particle& left, Particle& right,
			ParticleCollisionResult* collision_result
			);

	private:

		Real detection_precision_;
	};

	//class ParticleCollision
	//其实就是对心碰撞 处理对心碰撞而不是判断对心碰撞
	class ParticleCollision
	{
	public:

		ParticleCollision(Real restitution_coefficient = 1.0) :
			restitution_coefficient_(restitution_coefficient) {}

		ParticleCollision& set_restitution_coefficient(
			Real restitution_coeffient)
		{
			restitution_coefficient_ = restitution_coeffient;
		}

		Real get_restitution_coefficient() const
		{
			return restitution_coefficient_;
		}

		void operator()(const ParticleCollisionResult& particle_collision_result);

	private:

		Real restitution_coefficient_;
	}; //class ParticleCollision

} //namespace grid


#endif //_GRID_PARTICLE_COLLISION_H_