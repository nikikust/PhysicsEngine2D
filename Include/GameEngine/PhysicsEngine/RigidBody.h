#pragma once
#include <GameEngine/PhysicsEngine/Fixture.h>
#include <GameEngine/PhysicsEngine/PhysMath.h>
#include <GameEngine/PhysicsEngine/DAABBTree.h>
#include <GameEngine/PhysicsEngine/Shapes/CircleShape.h>
#include <GameEngine/PhysicsEngine/Shapes/PolygonShape.h>

#include <GameEngine/PhysicsEngine/Callbacks/RayCastCallback.h>


namespace physics
{
    class RigidBody;

    struct RigidBodyNodeData
    {
        RigidBodyNodeData(RigidBody* body_in);

        RigidBody* body;
        int32_t id;

        ShapeAABB aabb;
        int32_t node_id = nullnode;
    };

    struct RigidBodyRayCastWrapper
    {
        void raycast_callback(void* data)
        {
            FixtureNodeData* fixture_data = (FixtureNodeData*)data;
            Fixture* fixture = fixture_data->fixture;

            RayHitInfo output;

            bool hit = fixture->cast_ray(ray, output);

            if (hit)
            {
                return callback->report_fixture(fixture, output);
            }
        }

        RayCastCallback* callback;
        Ray ray;
    };

    class RigidBody
    {
    public:
        RigidBody();
        RigidBody(RigidBody&) = delete;
        RigidBody(RigidBody&&) noexcept;
        ~RigidBody();

        // --- Physics
        RigidBody& set_position             (const Vector& position            );
        RigidBody& set_angle                (float         angle               );
        RigidBody& set_linear_speed         (const Vector& linear_speed        );
        RigidBody& set_angular_speed        (float         angular_speed       );
        RigidBody& set_linear_acceleration  (const Vector& linear_acceleration );
        RigidBody& set_angular_acceleration (float         angular_acceleration);
        RigidBody& set_force                (const Vector& force               );

        RigidBody& set_linear_fixation  (bool x, bool y);
        RigidBody& set_angular_fixation (bool a);

        const Vector&    get_position             () const;
        float            get_angle                () const;
        const Transform& get_transform            () const;
        const Vector&    get_linear_speed         () const;
        float            get_angular_speed        () const;
        const Vector&    get_linear_acceleration  () const;
        float            get_angular_acceleration () const;
        const Vector&    get_force                () const;

        float get_inv_mass() const;
        float get_inv_mmoi() const;

        std::pair<bool, bool> get_linear_fixation  ();
        bool                  get_angular_fixation ();

        // --- Dynamics
        RigidBody& move       (const Vector& delta);
        RigidBody& accelerate (const Vector& delta);
        RigidBody& rotate     (float angle);
        RigidBody& spin       (float angle);

        // --- //
        void update(float delta_time, const Vector& gravity);

        void update_internal_AABB();
        void update_internal_AABB(const Vector offset);

        ShapeAABB get_AABB() const;

        RigidBodyNodeData* get_node_data() const;
        void set_node_data(RigidBodyNodeData* data);

        // --- Shapes
        physics::Fixture* add_shape (physics::Shape* shape);

        physics::Fixture* get_fixture    (uint32_t id) const;
        void              remove_fixture (uint32_t id);

        void set_active_fixture(uint32_t id, bool flag);

        const std::vector<physics::Fixture*>& get_fixtures() const;

        const DAABBTree& get_tree() const;
        DAABBTree& get_tree();

        // --- //
        int32_t get_id() const;

    private:
        void update_physical_data();
        void update_physical_data_append(physics::Fixture* fixture);
        void update_physical_data_remove(physics::Fixture* fixture);

#ifdef DAMPING
        void dump_speed(float delta_time);
#endif // DAMPING

        // --- Data
        Transform    transform_       = {};

        Vector linear_speed_          = {};
        float  angular_speed_         = 0;

        Vector linear_acceleration_   = {};
        float  angular_acceleration_  = 0;

        Vector force_                 = {};

        PhysicalData physical_data_   = {};

        // --- Flags
        std::pair<bool, bool> fixed_linear_ = {}; // x and y
        bool                  fixed_angle_  = false;
        
        // --- Shapes
        std::vector<physics::Fixture*> fixtures_;
        std::vector<physics::Fixture*> active_fixtures_;
        DAABBTree internal_tree_;

        RigidBodyNodeData* node_data_;

        // --- //

        int32_t id_;

        static int32_t max_body_id_;
    };

    using RigidBodyPtrPair = std::pair<RigidBody*, RigidBody*>;
} // namespace physics

#include "RigidBody.inl"
