#pragma once
#include <GameEngine/PhysicsEngine/RigidBody.h>
#include <GameEngine/PhysicsEngine/DAABBTree.h>
#include <GameEngine/PhysicsEngine/CollisionSolver.h>

#include <GameEngine/PhysicsEngine/Callbacks/RayCastCallback.h>
#include <GameEngine/PhysicsEngine/Callbacks/CollisionListener.h>


#ifdef DEBUG
#include <GameEngine/GUIEngine/Painter.h>
#endif // DEBUG


namespace physics
{
    struct WorldRayCastWrapper
    {
        void raycast_callback(void* data)
        {
            RigidBodyNodeData* body_data = (RigidBodyNodeData*)data;

            RigidBodyRayCastWrapper wrapper{ callback, ray };

            RigidBody* body = body_data->body;

            body->get_tree().cast_ray(&wrapper, ray);
        }

        RayCastCallback* callback;
        Ray ray;
    };

    class World
    {
    public:
        World();
        ~World();

        
        /// @brief Updates physics of the world
        /// @param delta_time - Time elapsed from previous update
        void update(float delta_time);

        /// Get id of the body
        physics::RigidBody* get_body(int32_t id) const;

        /// Add body to this world
        void add_body(physics::RigidBody* body);

        /// Get reference to the map of all bodies in this world stored under their IDs
        const std::unordered_map<int32_t, physics::RigidBody*>& get_bodies() const;

        /// Set gravity in this world
        void set_gravity(const Vector& acceleration);

        /// Query ray cast test
        void cast_ray(RayCastCallback* callback, const physics::Ray& ray);

        /// Removes all bodies from this world
        void clear();

        /// Register a collision event listener
        void set_collision_listener(CollisionListener* listener);

#ifdef DEBUG
        const std::vector<graphics::DebugDraw>& get_debug_entities();
#endif // DEBUG

    private:
        friend class DAABBTree;

        /// Searches contacts in global DAABB tree
        void update_bodies_contacts();

        /// Searches contacts in local DAABB trees of contacted bodies
        void update_fixtures_contacts();

        /// Removes false contacts
        void collide_fixtures();

        /// Solve contacts
        void solve_contacts();

        /// Integrate position and rotation
        void update_bodies(float delta_time);

        /// @brief Callback method for global DAABB tree collisions (called from query of update_bodies_contacts())
        /// @param data - RigidBodyNodeData* - data about collided body
        void add_contact_bodies(void* data);

        /// @brief Callback method for local bodies DAABB tree collisions (called from query of update_fixtures_contacts())
        /// @param data_1 FixtureNodeData* - data about 1st collided fixture
        /// @param data_2 FixtureNodeData* - data about 2nd collided fixture
        void add_contact_fixtures(void* data_1, void* data_2);

    private:
        Vector gravity_;

        std::unordered_map<int32_t, physics::RigidBody*> bodies_;

        DAABBTree world_tree_;

        RigidBody* contact_1_;
        std::vector<RigidBodyPtrPair> body_contacts_;
        std::vector<CollisionContact> fixture_contacts_;

    private:
        int32_t id_;
        static int32_t max_world_id;

#ifdef DEBUG
        std::vector<graphics::DebugDraw> debug_entities;
#endif // DEBUG


    private:
        CollisionSolver collision_solver_;

        CollisionListener* collision_listener_;
    };
} // namespace physics
