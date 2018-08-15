//gr_particle_collision.cpp

#include"include/gr_particle_collision.h"

namespace grid
{
	bool ParticleCollisionDetection::operator()(
		Particle& left, Particle& right,
		ParticleCollisionResult* collision_result
		)
	{
		Vector left_position(left.get_position());
		Vector right_position(right.get_position());
		Real distance = (left_position - right_position).length();
		if (distance <= detection_precision_)
		{
			collision_result->particle[0] = &left;
			collision_result->particle[1] = &right;
			collision_result->collision_position =
				(left.get_position() + right.get_position())*0.5;
			collision_result->collision_normal = 
				(left_position - right_position).normalize();
			collision_result->collision_depth = distance;
			return true;
		}
		else
		{
			return false;
		}
	}

	//-------------------------------------------------------//

	void ParticleCollision::operator()(
		const ParticleCollisionResult& particle_collision_result
		)
	{
		Vector v10 = 
			particle_collision_result.particle[0]->get_velocity();
		Vector v20 = 
			particle_collision_result.particle[1]->get_velocity();
		Real inv_m1 = 
			particle_collision_result.particle[0]->get_inverse_mass();
		Real inv_m2 = 
			particle_collision_result.particle[1]->get_inverse_mass();
		Vector v1 = v10;
		Vector v2 = v20;
		if (inv_m1 != 0.0 && inv_m2 != 0.0)
		{
			v1 = v10 - (v10 - v20)*((1.0 / (1.0 + inv_m2 / inv_m1)) * (1.0 + restitution_coefficient_));
			v2 = v20 + (v10 - v20)*((1.0 / (1.0 + inv_m1 / inv_m2)) * (1.0 + restitution_coefficient_));
		}
		else if (inv_m1 != 0.0 && inv_m2 == 0.0)
		{
			v1 = -v10;//对于这两种情况下 系统的动量其实是不守恒的 有的时候为了实现一些效果 应该附加额外的代码
			v2 = v20;
		}
		else if (inv_m1 == 0.0 && inv_m2 != 0.0)
		{
			v1 = v10;
			v2 = -v20;
		}
		particle_collision_result.particle[0]->set_velocity(v1);
		particle_collision_result.particle[1]->set_velocity(v2);
	}
} //namespace grid