#pragma once
#include <GameEngine/PhysicsEngine/RigidBody.h>
#include <GameEngine/PhysicsEngine/CollisionContact.h>

#ifdef DEBUG
#include <GameEngine/GUIEngine/Painter.h>
#endif // DEBUG


namespace physics
{
    struct ContactPointsInfo
    {
        Vector collision_point_1;   // 1st for: circ - circ, circ - poly, poly - poly
        Vector collision_point_2;   // 2nd for: poly - poly
        int32_t      collision_point_cnt;
    };

    class CollisionSolver
    {
    public:
        CollisionSolver();


        bool collide(CollisionContact& collision) const;
        
        void separate_bodies(const CollisionContact& collision, RigidBody* body_A, RigidBody* body_B) const;

        void write_collision_points(CollisionContact& collision, Fixture* fixture_A, Fixture* fixture_B, 
                                    const Transform& transform_A, const Transform& transform_B) const;

        void resolve_collision_basic(const CollisionContact& collision, RigidBody* body_A, RigidBody* body_B) const;

        void resolve_collision_with_rotation(const CollisionContact& collision, RigidBody* body_A, RigidBody* body_B) const;

#ifdef DEBUG
        static std::vector<graphics::DebugDraw> debug_entities;
#endif // DEBUG

    private:
        bool circles_collision        (CollisionContact& collision) const;
        bool polygons_collision       (CollisionContact& collision) const;
        bool polygon_circle_collision (CollisionContact& collision) const;
        bool circle_polygon_collision (CollisionContact& collision) const;

        std::pair<float, float> polygon_projection (PolygonShape* polygon, const Vector& axis, const Transform& transform) const;
        std::pair<float, float> circle_projection  (CircleShape*  circle,  const Vector& axis, const Transform& transform) const;

        Vector circle_polygon_closest_point(PolygonShape* polygon, CircleShape* circle, const Transform& transform_A, const Transform& transform_B) const;

        Vector circles_collision_points        (Shape* circle_A_raw,  Shape* circle_B_raw,  const Transform& transform_A, const Transform& transform_B) const;
        Vector circle_polygon_collision_points (Shape* polygon_raw,   Shape* circle_raw,    const Transform& transform_A, const Transform& transform_B) const;
        Vector polygons_collision_points       (Shape* polygon_A_raw, Shape* polygon_B_raw, const Transform& transform_A, const Transform& transform_B) const;
    };
} // namespace physics
