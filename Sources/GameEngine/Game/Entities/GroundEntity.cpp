#include <GameEngine/Game/Entities/GroundEntity.h>


namespace game
{
    GroundEntity::GroundEntity(std::shared_ptr<physics::World> world, const sf::Vector2f& position, float angle)
        : Entity({ 127, 127, 127 })
    {
        const float half_length = 25;
        const float half_width = 25;

        int32_t count = 40;

        std::vector<sf::Vector2f> base_vector{
            {-half_length, -half_width}, { half_length, -half_width},
            { half_length,  half_width}, {-half_length,  half_width}
        };
        
        sf::Vector2f offset_left { utils::rotate_point({ -half_length * 2, 0.f},  (float)PI2 / 7.f) };
        sf::Vector2f offset_right{ utils::rotate_point({  half_length * 2, 0.f}, -(float)PI2 / 7.f) };

        for (int32_t i = 0; i < count; ++i)
        {
            auto polygon_1 = new physics::PolygonShape(
                physics::rotate_polygon(base_vector, {},  (float)PI2 / 7.f), // Vertices
                offset_left * (i + 0.5f)                                     // Position
            );

            auto polygon_2 = new physics::PolygonShape(
                physics::rotate_polygon(base_vector, {}, -(float)PI2 / 7.f), // Vertices
                offset_right * (i + 0.5f)                                    // Position
            );

            main_body_->add_shape(polygon_1)->set_restitution(0.6f);
            main_body_->add_shape(polygon_2)->set_restitution(0.6f);
        }

        main_body_->set_position(position)
                   .set_angle(angle)
                   .set_angular_fixation(true)
                   .set_linear_fixation(true, true);

        world->add_body(main_body_);
    }

    GroundEntity::~GroundEntity()
    {
    }


    void GroundEntity::render(graphics::Painter& painter) const
    {
        auto& transform = main_body_->get_transform();
        auto& fixtures  = main_body_->get_fixtures();

        std::vector<sf::Vector2f> rotated_vertices;

        for (auto& fixture : fixtures)
        {
            auto shape = (physics::PolygonShape*)(fixture->get_shape());

            painter.draw_polygon(transform.position, physics::rotate_polygon(shape->get_vertices(), shape->get_position(), transform), color_);
        }
    }
} // namespace game
