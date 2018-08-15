//file anno

#ifndef _GRID_PARTICLE_H_
#define _GRID_PARTICLE_H_

#include"gr_vector.h"
#include<cassert>

namespace grid
{
	//class Particle
	class Particle
	{
	public:

		Particle() :
			inverse_mass_(1.0),
			position_(),
			velocity_() {}

		Particle(Real inverse_mass, Vector position, Vector velocity) :
			inverse_mass_(inverse_mass),
			position_(position_),
			velocity_(velocity) 
		{
			assert(inverse_mass_ >= 0.0);
		}

		Particle& set_inverse_mass(Real inverse_mass)
		{
			assert(inverse_mass >= 0.0);
			inverse_mass_ = inverse_mass;
			return *this;
		}

		Particle& set_position(const Vector& position)
		{
			position_ = position;
			return *this;
		}

		Particle& set_velocity(const Vector& velocity)
		{
			velocity_ = velocity;
			return *this;
		}

		Real get_inverse_mass() const
		{
			return inverse_mass_;
		}

		Vector get_position()const
		{
			return position_;
		}

		Vector get_velocity() const
		{
			return velocity_;
		}

	private:

		Real inverse_mass_;

		Vector position_;

		Vector velocity_;
	}; //class Particle

} //namespace gid

#endif //_GRID_PARTICLE_H_