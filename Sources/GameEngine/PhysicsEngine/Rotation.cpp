#include <GameEngine/PhysicsEngine/Rotation.h>


namespace physics
{
	Rotation::Rotation() : angle_(0.f), sin_(0.f), cos_(1.f) {}

	Rotation::Rotation(float angle) : angle_(angle), sin_(sinf(angle)), cos_(cosf(angle)) {}

	Rotation::Rotation(Rotation& rotation) : angle_(rotation.angle_), sin_(rotation.sin_), cos_(rotation.cos_) {}
	Rotation::Rotation(Rotation&& rotation) noexcept
		: angle_(std::move(rotation.angle_)), sin_(std::move(rotation.sin_)), cos_(std::move(rotation.cos_)) {}


	Rotation& Rotation::operator=(const Rotation& b)
	{
		this->angle_ = b.angle_;
		this->sin_ = b.sin_;
		this->cos_ = b.cos_;

		return *this;
	}
} // namespace physics
