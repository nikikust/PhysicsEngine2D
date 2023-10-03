#pragma once
#include <GameEngine/Utils/Functions.h>
#include <GameEngine/PhysicsEngine/RigidBody.h>

#ifdef DEBUG
#include <GameEngine/GUIEngine/Painter.h>
#endif // DEBUG


namespace physics
{
    struct ContactsInfo
    {
        sf::Vector2f collision_point_1;   // 1st for: circ - circ, circ - poly
        sf::Vector2f collision_point_2;   // 2nd for: poly - poly
        int32_t      collision_point_cnt;
    };

    struct CollisionInfo
    {
        sf::Vector2f contact_point;
        sf::Vector2f collision_normal;

        float depth;
        float elasticity;
    };

    class CollisionSolver
    {
    public:
        CollisionSolver();


        std::optional<CollisionInfo> collide(std::shared_ptr<Fixture> fixture_A, std::shared_ptr<Fixture> fixture_B, 
                                             const Transform& transform_A, const Transform& transform_B);
        
        void separate_bodies(const CollisionInfo& collision, RigidBody* body_A, RigidBody* body_B) const;

        void write_collision_points(CollisionInfo& collision, std::shared_ptr<Fixture> fixture_A, std::shared_ptr<Fixture> fixture_B, 
                                    const Transform& transform_A, const Transform& transform_B);

        void resolve_collision_basic(const CollisionInfo& collision, RigidBody* body_A, RigidBody* body_B) const;

        void resolve_collision_with_rotation(const CollisionInfo& collision, RigidBody* body_A, RigidBody* body_B) const;

#ifdef DEBUG
        static std::vector<graphics::DebugDraw> debug_entities;
#endif // DEBUG

    private:
        std::optional<CollisionInfo> circles_collision        (std::shared_ptr<Fixture> circle_A_raw,  std::shared_ptr<Fixture> circle_B_raw,  const Transform& transform_A, const Transform& transform_B) const;
        std::optional<CollisionInfo> polygons_collision       (std::shared_ptr<Fixture> polygon_A_raw, std::shared_ptr<Fixture> polygon_B_raw, const Transform& transform_A, const Transform& transform_B) const;
        std::optional<CollisionInfo> polygon_circle_collision (std::shared_ptr<Fixture> polygon_raw,   std::shared_ptr<Fixture> circle_raw,    const Transform& transform_A, const Transform& transform_B) const;
        std::optional<CollisionInfo> circle_polygon_collision (std::shared_ptr<Fixture> circle_raw,    std::shared_ptr<Fixture> polygon_raw,   const Transform& transform_A, const Transform& transform_B) const;

        std::pair<float, float> polygon_projection (std::shared_ptr<PolygonShape> polygon, const sf::Vector2f& axis, const Transform& transform) const;
        std::pair<float, float> circle_projection  (std::shared_ptr<CircleShape>  circle,  const sf::Vector2f& axis, const Transform& transform) const;

        sf::Vector2f circle_polygon_closest_point(std::shared_ptr<PolygonShape> polygon, std::shared_ptr<CircleShape> circle, Transform transform_A, Transform transform_B) const;

        sf::Vector2f circles_collision_points        (std::shared_ptr<Shape> circle_A_raw,  std::shared_ptr<Shape> circle_B_raw,  const Transform& transform_A, const Transform& transform_B) const;
        sf::Vector2f circle_polygon_collision_points (std::shared_ptr<Shape> polygon_raw,   std::shared_ptr<Shape> circle_raw,    const Transform& transform_A, const Transform& transform_B) const;
        sf::Vector2f polygons_collision_points       (std::shared_ptr<Shape> polygon_A_raw, std::shared_ptr<Shape> polygon_B_raw, const Transform& transform_A, const Transform& transform_B) const;

    };
} // namespace physics
