#include <GameEngine/Game/Entities/ShipEntity.h>


namespace game
{
    ShipEntity::ShipEntity(std::shared_ptr<physics::World> world, const sf::Vector2f& position, float angle)
        : Entity(sf::Color::Red), body_(std::make_shared<physics::RigidBody>())
    {
        const float half_length = 5;
        const float half_width  = 2;

        std::vector<sf::Vector2f> box{ {-half_length, -half_width}, { half_length, -half_width}, 
                                       { half_length,  half_width}, {-half_length,  half_width} };

        int32_t max_x = 75, max_y = 75;

        for (int32_t x = 0; x < max_x; ++x)
        {
            for (int32_t y = 0; y < max_y; ++y)
            {
                sf::Vector2f hor_center{ half_length + half_length * 2 * x, half_length * 2 * y };
                sf::Vector2f ver_center{ half_length * 2 * x, half_length + half_length * 2 * y };

                physics::PolygonShape bar_hor{ physics::rotate_polygon(box, {},        0.f), hor_center };
                physics::PolygonShape bar_ver{ physics::rotate_polygon(box, {}, (float)PI2), ver_center };

                if (x < max_x - 1)
                {
                    auto fixture = body_->add_shape(bar_hor);

                    if (utils::in(1, y, max_y - 2))
                        fixture->set_sleeping(true);
                }
                if (y < max_y - 1)
                {
                    auto fixture = body_->add_shape(bar_ver);

                    if (utils::in(1, x, max_x - 2))
                        fixture->set_sleeping(true);
                }
            }
        }

        body_->set_position(position);
        body_->set_angle(angle);

        world->add_body(body_);
    }


    void ShipEntity::render(graphics::Painter& painter)
    {
        auto& transform = body_->get_transform();
        auto& fixtures  = body_->get_fixtures();

        std::vector<sf::Vector2f> rotated_vertices;

        sf::Color color = color_;

        for (auto& fixture : fixtures)
        {
            if (fixture->is_sleeping())
                continue;

            auto shape = std::dynamic_pointer_cast<physics::PolygonShape>(fixture->get_shape());

            if (fixture->get_node_data()->is_sleeping)
                color = color_;
            else
                color = sf::Color::Green;

            painter.draw_polygon(transform.position, physics::rotate_polygon(shape->get_vertices(), shape->get_position(), transform), color);
        }
    }

    const std::shared_ptr<physics::RigidBody>& ShipEntity::get_body() const
    {
        return body_;
    }
} // namespace game
