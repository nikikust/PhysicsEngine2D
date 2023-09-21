#include <GameEngine/PhysicsEngine/Fixture.h>
#include <GameEngine/PhysicsEngine/RigidBody.h>


namespace physics
{
	Fixture::Fixture(std::shared_ptr<Shape> shape, physics::RigidBody* body)
		: shape_(shape), body_(body)
	{
		restitution_ = 0.6f;
		friction_    = 0.0f;
		density_     = 0.0f;
	}


	const std::shared_ptr<Shape>& Fixture::get_shape() const
	{
		return shape_;
	}

	float Fixture::get_restitution() const
	{
		return restitution_;
	}
	Fixture& Fixture::set_restitution(float restitution)
	{
		restitution_ = restitution;

		return *this;
	}
} // namespace physics
