#pragma once
#include <GameEngine/PhysicsEngine/Shapes/Shape.h>


namespace physics
{
	class RigidBody;

	class Fixture
	{
	public:
		Fixture(std::shared_ptr<Shape> shape, RigidBody* body);


		// --- //
		const std::shared_ptr<Shape>& get_shape() const;

		float    get_restitution() const;
		Fixture& set_restitution(float restitution);

	private:
		std::shared_ptr<Shape> shape_;
		physics::RigidBody*    body_;

		float restitution_;
		float friction_;
		float density_;
	};
} // namespace physics
