#pragma once
#include <GameEngine/PhysicsEngine/Shapes/Shape.h>


namespace physics
{
	class RigidBody;

	class Fixture
	{
	public:
		Fixture(std::shared_ptr<Shape> shape);


		// --- //
		const std::shared_ptr<Shape>& get_shape() const;

		float    get_restitution() const;
		Fixture& set_restitution(float restitution);
		
		// --- Physical data
		bool update_physical_data();

		const PhysicalData& get_physical_data() const;
		PhysicalData        get_physical_data(const sf::Vector2f axis) const;

		bool has_shape();

	private:
		std::shared_ptr<Shape> shape_;

		PhysicalData physical_data_;

		float restitution_;
		float friction_;
		float density_;
	};
} // namespace physics
