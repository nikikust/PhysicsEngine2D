#include <GameEngine/Game/Entities/ShipEntity.h>


namespace game
{
	ShipEntity::ShipEntity(std::shared_ptr<physics::World> world, const sf::Vector2f& position, float angle)
		: Entity(sf::Color::Red)
	{
		std::vector<sf::Vector2f> box{ {-25, -5}, {25, -5}, {25, 5}, {-25, 5} };

		physics::RigidBody body;

		int32_t max_x = 16, max_y = 16;

		for (int32_t x = 0; x < max_x; ++x)
		{
			for (int32_t y = 0; y < max_y; ++y)
			{
				sf::Vector2f hor_center{ 25 + 50.f * x,      50.f * y };
				sf::Vector2f ver_center{      50.f * x, 25 + 50.f * y };

				physics::PolygonShape bar_hor{ physics::rotate_polygon(box, {},        0.f), hor_center };
				physics::PolygonShape bar_ver{ physics::rotate_polygon(box, {}, (float)PI2), ver_center };


				if (x < max_x - 1)
					body.add_shape(bar_hor)->set_restitution(0.6f);

				if (y < max_y - 1)
					body.add_shape(bar_ver)->set_restitution(0.6f);
			}
		}

		body_ = world->add_body(body);

		body_->set_position(position);
		body_->set_angle(angle);
	}


	void ShipEntity::render(graphics::Painter& painter)
	{
		auto& transform = body_->get_transform();
		auto& fixtures  = body_->get_fixtures();

		std::vector<sf::Vector2f> rotated_vertices;

		for (auto& fixture : fixtures)
		{
			auto shape = std::dynamic_pointer_cast<physics::PolygonShape>(fixture->get_shape());

			painter.draw_polygon(transform.position, physics::rotate_polygon(shape->get_vertices(), shape->get_position(), transform), color_);
		}

	}

	const std::shared_ptr<physics::RigidBody>& ShipEntity::get_body() const
	{
		return body_;
	}
} // namespace game
