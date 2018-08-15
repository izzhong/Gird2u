//gr_constraint.h

//TODO(zhong) : surroundconstraint 实现思考
//				可以想象成一个跟屁虫跟着你跑 
//				当你们的距离超过一定范围 就跟随你的速度 并设置最大速度上限
//				当你停下的时候 根据当前距离计算出一定时间内的匀减速直线运动 并运动至约束位置

#ifndef _GRID_CONSTRAINT_H_
#define _GRID_CONSTRAINT_H_

#include"gr_particle.h"

namespace grid
{
	//class ParticleConstraint
	class ParticleConstraint
	{
	public:
		virtual void operator()(Particle* particle) = 0;
	}; //class ParticleConstraint

	//class FixParticleConstraint
	class FixParticleConstraint :
		public ParticleConstraint
	{
	public:

		FixParticleConstraint() :
			fix_position_(), fix_vector_() {}

		FixParticleConstraint(const Vector& fix_position,
			const Vector& fix_vector) :
			fix_position_(fix_position),
			fix_vector_(fix_vector) {}

		FixParticleConstraint& set_fix_position(
			const Vector& fix_position
		) {
			fix_position_ = fix_position;
			return *this;
		}

		FixParticleConstraint& set_fix_vector(
			const Vector& fix_vector
		) {
			fix_vector_ = fix_vector;
			return *this;
		}

		Vector get_fix_position() const
		{
			return fix_position_;
		}

		Vector get_fix_vector() const
		{
			return fix_vector_;
		}

		virtual void operator()(Particle* particle) override
		{
			if (particle->get_position() !=
				fix_position_ + fix_vector_)
			{
				particle->set_position(fix_position_ +
					fix_vector_);
			}
		}

	protected:

		Vector fix_position_;

		Vector fix_vector_;
	}; //class FixParticleConstraint

	//class SurroundParticleConstraint
	class SurroundParticleConstraint :
		public FixParticleConstraint
	{
	public:

		SurroundParticleConstraint() :
			FixParticleConstraint(),
			rotate_speed_(0.0),
			sensitivity_(1.0) {}

		SurroundParticleConstraint(
			const Vector& fix_position,
			const Vector& fix_vector,
			Real rotate_speed,
			Real sensitivity) :
			FixParticleConstraint(fix_position, fix_vector),
			rotate_speed_(rotate_speed), sensitivity_(sensitivity) {}

		SurroundParticleConstraint& set_rotate_speed(Real rotate_speed)
		{
			rotate_speed_ = rotate_speed;
			return *this;
		}

		Real get_rotate_speed() const
		{
			return rotate_speed_;
		}

		virtual void operator()(Particle* particle) override;

	private:
		
		Real rotate_speed_;

		Real sensitivity_;

	}; //namespace grid

} //namespace grid

#endif //_GRID_CONSTRAINT_H_