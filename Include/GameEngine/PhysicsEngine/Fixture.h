#pragma once
#include <GameEngine/PhysicsEngine/Shapes/Shape.h>
#include <GameEngine/PhysicsEngine/ShapeAABB.h>


namespace physics
{
	class RigidBody;

	class Fixture
	{
	public:
		Fixture(std::shared_ptr<Shape> shape);


		// --- //
		const std::shared_ptr<Shape>& get_shape() const;
		ShapeAABB get_AABB(const Transform& transform);

		float    get_restitution() const;
		Fixture& set_restitution(float restitution);
		
		// --- Physical data
		bool update_physical_data();

		const PhysicalData& get_physical_data() const;
		PhysicalData        get_physical_data(const sf::Vector2f axis) const;

		bool has_shape();

		bool is_sleeping();
		void set_sleeping(bool flag);

	private:
		std::shared_ptr<Shape> shape_;

		PhysicalData physical_data_;

		float restitution_;
		float friction_;
		float density_;

		bool sleeping_;

		// --- Cached values
		std::optional<Transform> cached_transform_;
		std::optional<ShapeAABB> cached_AABB;
	};
} // namespace physics
