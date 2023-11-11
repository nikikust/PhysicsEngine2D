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

    using FixturePtrPair = std::pair<Fixture*, Fixture*>;


    // Inline section
    inline Shape* Fixture::get_shape() const
    {
        return shape_;
    }

    inline FixtureNodeData* Fixture::get_node_data() const
    {
        return node_data_;
    }

    inline Fixture& Fixture::set_node_data(FixtureNodeData* data)
    {
        node_data_ = data;

        return *this;
    }

    inline float Fixture::get_restitution() const
    {
        return restitution_;
    }

    inline Fixture& Fixture::set_restitution(float restitution)
    {
        restitution_ = restitution;

        return *this;
    }

    inline const PhysicalData& Fixture::get_physical_data() const
    {
        return physical_data_;
    }

    inline PhysicalData Fixture::get_physical_data(const Vector axis) const
    {
        auto relative_physical_data = physical_data_;

        relative_physical_data.mmoi += relative_physical_data.mass * dot(axis, axis);

        return relative_physical_data;
    }

    inline RigidBody* Fixture::get_body() const
    {
        return body_;
    }

    inline int32_t Fixture::get_id() const
    {
        return shape_->get_id();
    }

    inline bool Fixture::has_shape()
    {
        return shape_ != nullptr;
    }

    inline bool Fixture::is_sleeping()
    {
        return node_data_->is_sleeping;
    }

} // namespace physics
