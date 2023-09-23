#pragma once
#include <GameEngine/PhysicsEngine/World.h>


namespace physics
{
    class Engine
    {
    public:
        Engine();
        Engine(Engine&) = delete;
        Engine(Engine&&) = delete;

        ~Engine();

        // --- //

        void update(float delta_time);

        std::shared_ptr<physics::RigidBody> get_body(int32_t id) const;
        std::shared_ptr<physics::RigidBody> get_body(int32_t id, int32_t world_id) const;

        std::shared_ptr<physics::RigidBody> add_body(const physics::RigidBody& body);

        std::shared_ptr<World> get_world();

    private:
        std::shared_ptr<World> selected_world_{};

        // Config
        static int32_t steps_amount;
    };
} // namespace physics
