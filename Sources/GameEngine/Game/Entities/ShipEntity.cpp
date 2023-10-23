#include <GameEngine/Game/Entities/ShipEntity.h>


namespace game
{
    ShipEntity::ShipEntity(std::shared_ptr<physics::World> world, const sf::Vector2f& position, float angle, int32_t max_x, int32_t max_y)
        : Entity(sf::Color::Red)
    {
        const float half_length = 5;
        const float half_width  = 2;

        std::vector<sf::Vector2f> box{ {-half_length, -half_width}, { half_length, -half_width},
                                       { half_length,  half_width}, {-half_length,  half_width} };

        for (int32_t x = 0; x < max_x; ++x)
        {
            for (int32_t y = 0; y < max_y; ++y)
            {
                sf::Vector2f hor_center{ half_length + half_length * 2 * x, half_length * 2 * y };
                sf::Vector2f ver_center{ half_length * 2 * x, half_length + half_length * 2 * y };

                auto bar_hor = new physics::PolygonShape(physics::rotate_polygon(box, {},        0.f), hor_center);
                auto bar_ver = new physics::PolygonShape(physics::rotate_polygon(box, {}, (float)PI2), ver_center);

                if (x < max_x - 1)
                {
                    auto fixture = main_body_->add_shape(bar_hor);

                    if (utils::in(1, y, max_y - 2))
                        fixture->set_sleeping(true);
                }
                if (y < max_y - 1)
                {
                    auto fixture = main_body_->add_shape(bar_ver);

                    if (utils::in(1, x, max_x - 2))
                        fixture->set_sleeping(true);
                }
            }
        }

        main_body_->set_position(position);
        main_body_->set_angle(angle);

        world->add_body(main_body_);
    }

    ShipEntity::~ShipEntity()
    {
    }


    void ShipEntity::render(graphics::Painter& painter) const
    {
        auto& transform = main_body_->get_transform();
        auto& fixtures  = main_body_->get_fixtures();

        std::vector<sf::Vector2f> rotated_vertices;

        sf::Color color = color_;

        for (const auto& fixture : fixtures)
        {
            if (fixture->is_sleeping())
                continue;

            auto shape = (physics::PolygonShape*)(fixture->get_shape());

            if (fixture->get_node_data()->is_sleeping)
                color = color_;
            else
                color = sf::Color::Green;

            painter.draw_polygon(transform.position, physics::rotate_polygon(shape->get_vertices(), shape->get_position(), transform), color);
        }
    }
} // namespace game
