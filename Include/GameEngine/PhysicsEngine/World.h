#pragma once
#include <GameEngine/Utils/Functions.h>
#include <GameEngine/PhysicsEngine/RigidBody.h>
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
        std::shared_ptr<physics::RigidBody> get_body(int32_t id) const;

        /// Add body to this world
        std::shared_ptr<physics::RigidBody> add_body(const physics::RigidBody& body);

        /// Get reference to the map of all bodies in this world stored under their IDs
        const std::unordered_map<int32_t, std::shared_ptr<physics::RigidBody>>& get_bodies();

#ifdef DEBUG
        const std::vector<graphics::DebugDraw>& get_debug_entities();
#endif // DEBUG

    private:
        /// Skip bodies which don't pass AABB check
        bool broad_check(const std::shared_ptr<physics::RigidBody>& body_A, 
                         const std::shared_ptr<physics::RigidBody>& body_B);
        

        /// Iterates throught fixtures of both bodies and resolves their collisions
        void update_body_pair(const std::shared_ptr<physics::RigidBody>& body_A, 
                              const std::shared_ptr<physics::RigidBody>& body_B);

        // Data

        static sf::Vector2f gravity_;

        std::unordered_map<int32_t, std::shared_ptr<physics::RigidBody>> bodies_{};

        // --- //

        int32_t id_;
        static int32_t max_world_id;

        CollisionSolver collision_solver_;
    };
} // namespace physics
