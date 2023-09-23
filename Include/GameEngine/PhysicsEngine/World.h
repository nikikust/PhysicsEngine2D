#pragma once
#include <GameEngine/Utils/Functions.h>
#include <GameEngine/PhysicsEngine/RigidBody.h>
#include <GameEngine/PhysicsEngine/CollisionSolver.h>


namespace physics
{
    class World
    {
    public:
        World();

        
        // --- //
        void update(float delta_time);

        std::shared_ptr<physics::RigidBody> get_body(int32_t id) const;

        std::shared_ptr<physics::RigidBody> add_body(const physics::RigidBody& body);

        const std::unordered_map<int32_t, std::shared_ptr<physics::RigidBody>>& get_bodies();

    private:
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
