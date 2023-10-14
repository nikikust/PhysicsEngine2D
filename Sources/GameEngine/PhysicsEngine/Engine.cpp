#include <GameEngine/PhysicsEngine/Engine.h>


namespace physics
{
    int32_t Engine::steps_amount = 16;


    Engine::Engine()
    {
        selected_world_ = std::make_shared<physics::World>();

        paused_ = true;
        do_step_ = false;
    }
    Engine::~Engine()
    {
    }


    void Engine::update(float delta_time, const sf::Vector2i& window_size)
    {
        if (paused_ && !do_step_)
            return;

        do_step_ = false;

        for (int step_cnt = 0; step_cnt < steps_amount; ++step_cnt)
            selected_world_->update(delta_time / steps_amount);

        for (auto& [k, body] : selected_world_->get_bodies())
            wrap_to_area(body, window_size * 2);
    }

    physics::RigidBody* Engine::get_body(int32_t id) const
    {
        return selected_world_->get_body(id);
    }
    physics::RigidBody* Engine::get_body(int32_t id, int32_t world_id) const
    {
        // TO DO: world selection
        return selected_world_->get_body(id);
    }

    void Engine::add_body(physics::RigidBody* body)
    {
        return selected_world_->add_body(body);
    }

    std::shared_ptr<World> Engine::get_world()
    {
        // TO DO: world selection
        return selected_world_;
    }

    void Engine::set_pause(bool flag)
    {
        paused_ = flag;
    }

    bool Engine::get_pause_state()
    {
        return paused_;
    }

    void Engine::do_step()
    {
        do_step_ = true;
    }

#ifdef DEBUG
    const std::vector<graphics::DebugDraw>& Engine::get_debug_entities()
    {
        return selected_world_->get_debug_entities();
    }
#endif // DEBUG


    void Engine::wrap_to_area(RigidBody* body, const sf::Vector2i& window_size)
    {
        auto& position = body->get_position();

        sf::Vector2f pos{
            (position.x + window_size.x / 4.f) / (float)window_size.x,
            (position.y + window_size.y / 4.f) / (float)window_size.y
        };

        if (pos.x < 0)
            pos.x = 1.f - fmodf(fabsf(pos.x), 1.f);
        else if (pos.x > 1)
            pos.x = fmodf(pos.x, 1.f);

        if (pos.y < 0)
            pos.y = 1.f - fmodf(fabsf(pos.y), 1.f);
        else if (pos.y > 1)
            pos.y = fmodf(pos.y, 1.f);

        pos.x *= (float)window_size.x; pos.x -= window_size.x / 4.f;
        pos.y *= (float)window_size.y; pos.y -= window_size.y / 4.f;

        body->set_position(pos);
    }
} // namespace physics
