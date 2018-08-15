//gr_constraint.h

//TODO(zhong) : surroundconstraint ʵ��˼��
//				���������һ����ƨ��������� 
//				�����ǵľ��볬��һ����Χ �͸�������ٶ� ����������ٶ�����
//				����ͣ�µ�ʱ�� ���ݵ�ǰ��������һ��ʱ���ڵ��ȼ���ֱ���˶� ���˶���Լ��λ��

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