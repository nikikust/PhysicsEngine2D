#pragma once
#include <GameEngine/PhysicsEngine/Shapes/Shape.h>
#include <GameEngine/PhysicsEngine/ShapeAABB.h>
#include <GameEngine/PhysicsEngine/DAABBTree.h>


namespace physics
{
    class RigidBody;
    class Fixture;

    struct FixtureNodeData
    {
        FixtureNodeData(Fixture* fixture_in, int32_t id_in);

        Fixture* fixture;
        int32_t id;
        bool is_sleeping = false;

        ShapeAABB aabb;
        int32_t node_id = nullnode;
    };

    class Fixture
    {
    public:
        Fixture(Shape* shape, RigidBody* body);
        ~Fixture();


        // --- //
        Shape* get_shape() const;

        const ShapeAABB& get_AABB();

        FixtureNodeData* get_node_data() const;
        Fixture& set_node_data(FixtureNodeData* data);

        float    get_restitution() const;
        Fixture& set_restitution(float restitution);

        bool cast_ray(const Ray& ray, RayHitInfo& output);
        
        // --- Physical data
        bool update_physical_data();

        const PhysicalData& get_physical_data() const;
        PhysicalData        get_physical_data(const Vector axis) const;

        RigidBody* get_body() const;
        int32_t    get_id() const;

        bool has_shape();

        bool is_sleeping();
        Fixture& set_sleeping(bool flag);

    private:
        Shape* shape_;
        RigidBody* body_;

        PhysicalData physical_data_;

        float restitution_;
        float friction_;
        float density_;

        // --- Cached values
        ShapeAABB base_AABB_;
        FixtureNodeData* node_data_;
    };
} // namespace physics

#include "Fixture.inl"
    
