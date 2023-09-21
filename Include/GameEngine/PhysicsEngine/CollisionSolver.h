#pragma once
#include <GameEngine/Utils/Functions.h>
#include <GameEngine/DataCore/DataStorage.h>

#include <GameEngine/PhysicsEngine/Shapes/PolygonShape.h>
#include <GameEngine/PhysicsEngine/Shapes/CircleShape.h>
#include <GameEngine/PhysicsEngine/RigidBody.h>
#include <GameEngine/PhysicsEngine/PhysMath.h>
#include <GameEngine/PhysicsEngine/Fixture.h>


namespace physics
{
	struct CollisionInfo
	{
		sf::Vector2f collision_point;
		sf::Vector2f collision_normal;

		float depth;
		float elasticity;
	};

	class CollisionSolver
	{
	public:
		CollisionSolver();

		std::optional<CollisionInfo> circles_collision        (std::shared_ptr<Fixture> circle_A_raw,  std::shared_ptr<Fixture> circle_B_raw , Transform transform_A, Transform transform_B);
		std::optional<CollisionInfo> polygons_collision       (std::shared_ptr<Fixture> polygon_A_raw, std::shared_ptr<Fixture> polygon_B_raw, Transform transform_A, Transform transform_B);
		std::optional<CollisionInfo> polygon_circle_collision (std::shared_ptr<Fixture> polygon_raw,   std::shared_ptr<Fixture> circle_raw   , Transform transform_A, Transform transform_B);
		std::optional<CollisionInfo> circle_polygon_collision (std::shared_ptr<Fixture> circle_raw,    std::shared_ptr<Fixture> polygon_raw  , Transform transform_A, Transform transform_B);

		std::pair<float, float> polygon_projection(std::shared_ptr<PolygonShape> polygon, const sf::Vector2f& axis, Transform transform);
		std::pair<float, float> circle_projection (std::shared_ptr<CircleShape>  circle,  const sf::Vector2f& axis, Transform transform);

		sf::Vector2f circle_polygon_closest_point(std::shared_ptr<PolygonShape> polygon, std::shared_ptr<CircleShape> circle, Transform transform_A, Transform transform_B);

		void resolve_collision_simple(const CollisionInfo& collision, std::shared_ptr<RigidBody> body_A, std::shared_ptr<RigidBody> body_B);
		void resolve_collision       (const CollisionInfo& collision, std::shared_ptr<RigidBody> body_A, std::shared_ptr<RigidBody> body_B);

	private:

	};
} // namespace physics
