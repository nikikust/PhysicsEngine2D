#include <GameEngine/PhysicsEngine/Rotation.h>


namespace physics
{
	Rotation::Rotation() : angle_(0.f), sin_(0.f), cos_(1.f) {}

	Rotation::Rotation(float angle) : angle_(angle), sin_(sinf(angle)), cos_(cosf(angle)) {}


	void Rotation::set_angle(float angle)
	{
		angle_ = angle;
		sin_ = sinf(angle_);
		cos_ = cosf(angle_);
	}
	void Rotation::rotate(float angle)
	{
		angle_ += angle;
		sin_ = sinf(angle_);
		cos_ = cosf(angle_);
	}
	float Rotation::get_angle() const
	{
		return angle_;
	}
	float Rotation::get_sin() const
	{
		return sin_;
	}
	float Rotation::get_cos() const
	{
		return cos_;
	}
} // namespace physics
