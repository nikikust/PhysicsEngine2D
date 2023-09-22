#include <GameEngine/PhysicsEngine/Engine.h>


namespace physics
{
    int32_t Engine::steps_amount = 16;


    Engine::Engine()
    {
    }
    Engine::~Engine()
    {
    }

    void Engine::update(float delta_time)
    {
        for (int step_cnt = 0; step_cnt < steps_amount; ++step_cnt)
            selected_world_.update(delta_time / steps_amount);
    }
    std::shared_ptr<physics::RigidBody> Engine::get_body(int32_t id)
    {
        return selected_world_.get_body(id);
    }
    std::shared_ptr<physics::RigidBody> Engine::get_body(int32_t id, int32_t world_id)
    {
        // TO DO: world selection
        return selected_world_.get_body(id);
    }

    std::shared_ptr<physics::RigidBody> Engine::add_body(const physics::RigidBody& body)
    {
        return selected_world_.add_body(body);
    }
} // namespace physics
