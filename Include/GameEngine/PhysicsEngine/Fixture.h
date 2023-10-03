#pragma once
#include <GameEngine/PhysicsEngine/Shapes/Shape.h>
#include <GameEngine/PhysicsEngine/ShapeAABB.h>


namespace physics
{
	class RigidBody;

	class Fixture;

	struct FixtureNodeData
	{
		FixtureNodeData(std::shared_ptr<Fixture> fixture_in, const ShapeAABB& aabb_in, int32_t id_in);

		std::weak_ptr<Fixture> fixture;
		int32_t id;

		ShapeAABB aabb;
		int32_t node_id;
	};

	class Fixture
	{
	public:
		Fixture(std::shared_ptr<Shape> shape, RigidBody* body);
		~Fixture();


		// --- //
		const std::shared_ptr<Shape>& get_shape() const;
		ShapeAABB get_AABB();

		FixtureNodeData* get_node_data() const;
		void set_node_data(FixtureNodeData* data);

		float    get_restitution() const;
		Fixture& set_restitution(float restitution);
		
		// --- Physical data
		bool update_physical_data();

		const PhysicalData& get_physical_data() const;
		PhysicalData        get_physical_data(const sf::Vector2f axis) const;

		bool has_shape();

		bool is_sleeping();
		Fixture& set_sleeping(bool flag);

	private:
		std::shared_ptr<Shape> shape_;
		RigidBody* body_;

		PhysicalData physical_data_;

		float restitution_;
		float friction_;
		float density_;

		bool sleeping_;

		// --- Cached values
		ShapeAABB base_AABB_;
		std::optional<ShapeAABB> cached_AABB_;
		std::optional<Transform> cached_transform_;
		FixtureNodeData* node_data_;
	};

	using FixturePtrPair = std::pair<std::shared_ptr<Fixture>, std::shared_ptr<Fixture>>;
} // namespace physics
