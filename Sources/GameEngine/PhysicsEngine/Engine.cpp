#include <GameEngine/PhysicsEngine/Engine.h>


namespace physics
{
    int32_t Engine::steps_amount = 16;


    Engine::Engine()
    {
        selected_world_ = std::make_shared<physics::World>();
    }
    Engine::~Engine()
    {
    }


    void Engine::update(float delta_time, const sf::Vector2i& window_size)
    {
        for (int step_cnt = 0; step_cnt < steps_amount; ++step_cnt)
            selected_world_->update(delta_time / steps_amount);

        for (auto& [k, body] : selected_world_->get_bodies())
            wrap_to_screen(body, window_size);
    }

    std::shared_ptr<physics::RigidBody> Engine::get_body(int32_t id) const
    {
        return selected_world_->get_body(id);
    }
    std::shared_ptr<physics::RigidBody> Engine::get_body(int32_t id, int32_t world_id) const
    {
        // TO DO: world selection
        return selected_world_->get_body(id);
    }

    std::shared_ptr<physics::RigidBody> Engine::add_body(const physics::RigidBody& body)
    {
        return selected_world_->add_body(body);
    }

    std::shared_ptr<World> Engine::get_world()
    {
        // TO DO: world selection
        return selected_world_;
    }



    void Engine::wrap_to_screen(std::shared_ptr<RigidBody> body, const sf::Vector2i& window_size)
    {
        auto& transfrom = body->get_transform();

        sf::Vector2f pos{
            transfrom.position.x / (float)window_size.x,
            transfrom.position.y / (float)window_size.y
        };

        if (pos.x < 0)
            pos.x = 1.f - fmodf(fabsf(pos.x), 1.f);
        else if (pos.x > 1)
            pos.x = fmodf(pos.x, 1.f);

        if (pos.y < 0)
            pos.y = 1.f - fmodf(fabsf(pos.y), 1.f);
        else if (pos.y > 1)
            pos.y = fmodf(pos.y, 1.f);

        pos.x *= (float)window_size.x;
        pos.y *= (float)window_size.y;

        body->set_transform({ pos, transfrom.angle });
    }
} // namespace physics
