#pragma once
#include <GameEngine/Utils/Functions.h>
#include <GameEngine/PhysicsEngine/RigidBody.h>
#include <GameEngine/PhysicsEngine/DAABBTree.h>
#include <GameEngine/PhysicsEngine/ContactsManager.h>
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
        void add_body(std::shared_ptr<physics::RigidBody> body);

        /// Get reference to the map of all bodies in this world stored under their IDs
        const std::unordered_map<int32_t, std::shared_ptr<physics::RigidBody>>& get_bodies();

#ifdef DEBUG
        const std::vector<graphics::DebugDraw>& get_debug_entities();
#endif // DEBUG

    private:
        friend class DAABBTree;

        void update_contacts();
        void add_contact(void* data);
        

        /// Iterates throught fixtures of both bodies and resolves their collisions
        void update_body_pair(const std::shared_ptr<physics::RigidBody>& body_A, 
                              const std::shared_ptr<physics::RigidBody>& body_B);

        // --- Data

        static sf::Vector2f gravity_;

        std::unordered_map<int32_t, std::shared_ptr<physics::RigidBody>> bodies_{};

        DAABBTree tree_;

        std::vector<RigidBodyPtrPair> contacts;
        std::shared_ptr<RigidBody> contact_1;

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
