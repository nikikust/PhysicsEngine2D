#include <GameEngine/PhysicsEngine/Engine.h>


namespace physics
{
    int32_t Engine::steps_amount = 2;


    Engine::Engine()
    {
        selected_world_ = std::make_shared<physics::World>();

        paused_ = true;
        do_step_ = false;
    }
    Engine::~Engine()
    {
    }


    void Engine::update(float delta_time)
    {
        if (paused_ && !do_step_)
            return;

        do_step_ = false;

        for (int step_cnt = 0; step_cnt < steps_amount; ++step_cnt)
            selected_world_->update(delta_time / steps_amount);

        // TODO: Acceleration tests
        // sf::Vector2f dir{ 1.f, 0.f };
        
        for (auto& [k, body] : selected_world_->get_bodies())
        {
            wrap_to_area(body, { -2400.f, -1500.f }, { 2400.f, 1500.f });
        
            // auto rot = utils::rotate_point(dir, body->get_angle());
            // 
            // body->accelerate(rot * (100000000.f * body->get_inv_mass()) * delta_time);
        }
    }

    physics::RigidBody* Engine::get_body(int32_t id) const
    {
        return selected_world_->get_body(id);
    }
    physics::RigidBody* Engine::get_body(int32_t id, int32_t world_id) const
    {
        // TODO: world selection
        return selected_world_->get_body(id);
    }

    void Engine::add_body(physics::RigidBody* body)
    {
        return selected_world_->add_body(body);
    }

    std::shared_ptr<World> Engine::get_world()
    {
        // TODO: world selection
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


    void Engine::wrap_to_area(RigidBody* body, const sf::Vector2f& area_min, const sf::Vector2f& area_max)
    {
        auto& position = body->get_position();

        sf::Vector2f pos{
            (position.x - area_min.x) / (area_max - area_min).x,
            (position.y - area_min.y) / (area_max - area_min).y
        };

        if (pos.x < 0)
            pos.x = 1.f - fmodf(fabsf(pos.x), 1.f);
        else if (pos.x > 1)
            pos.x = fmodf(pos.x, 1.f);

        if (pos.y < 0)
            pos.y = 1.f - fmodf(fabsf(pos.y), 1.f);
        else if (pos.y > 1)
            pos.y = fmodf(pos.y, 1.f);

        pos.x *= (area_max - area_min).x; pos.x += area_min.x;
        pos.y *= (area_max - area_min).y; pos.y += area_min.y;

        body->set_position(pos);
    }
} // namespace physics
