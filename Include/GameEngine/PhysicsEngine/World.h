#pragma once
#include <GameEngine/Utils/Functions.h>
#include <GameEngine/PhysicsEngine/RigidBody.h>
#include <GameEngine/PhysicsEngine/DAABBTree.h>
#include <GameEngine/PhysicsEngine/CollisionSolver.h>

#ifdef DEBUG
#include <GameEngine/GUIEngine/Painter.h>
#endif // DEBUG


namespace physics
{
    class World
    {
    public:
        World();

        
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
        void set_gravity(const sf::Vector2f& acceleration);

        /// Removes all bodies from this world
        void clear();

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
        void add_contact(void* data);

        /// @brief Callback method for local bodies DAABB tree collisions (called from query of update_fixtures_contacts())
        /// @param data_1 FixtureNodeData* - data about 1st collided fixture
        /// @param data_2 FixtureNodeData* - data about 2nd collided fixture
        void add_contact(void* data_1, void* data_2);

        // --- Data

        sf::Vector2f gravity_;

        std::unordered_map<int32_t, physics::RigidBody*> bodies_;

        DAABBTree world_tree_;

        RigidBody* contact_1_;
        std::vector<RigidBodyPtrPair> body_contacts_;
        std::vector<CollisionInfo> fixture_contacts_;

        // --- //

        int32_t id_;
        static int32_t max_world_id;

#ifdef DEBUG
        std::vector<graphics::DebugDraw> debug_entities;
#endif // DEBUG


        // --- //
        CollisionSolver collision_solver_;
    };
} // namespace physics
