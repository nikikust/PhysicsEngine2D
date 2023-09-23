#include <GameEngine/Game/Entities/ComplexEntity.h>


namespace game
{
	ComplexEntity::ComplexEntity(std::shared_ptr<physics::World> world, const sf::Vector2f& position, float angle)
		: Entity(sf::Color::Green)
	{
		physics::RigidBody body;

		physics::CircleShape circle{
			50,      // Radius
			{0, -50} // Position
		};

		physics::PolygonShape polygon{
			{ {-50, -50}, {50, -50}, {50, 50}, {-50, 50} }, // Vertices
			{0, 50} // Position
		};

		body.add_shape(circle) ->set_restitution(0.6f); // id: 0
		body.add_shape(polygon)->set_restitution(0.6f); // id: 1

		body_ = world->add_body(body);
		body_->set_transform({ position, angle });
	}


	void ComplexEntity::render(graphics::Painter& painter)
	{
		auto& transform = body_->get_transform();

		auto c_shape = std::dynamic_pointer_cast<physics::CircleShape> (body_->get_fixtures().at(0)->get_shape());
		auto p_shape = std::dynamic_pointer_cast<physics::PolygonShape>(body_->get_fixtures().at(1)->get_shape());

		auto rotated_center = physics::rotate_point(c_shape->get_position(), transform);

		auto rotated_vertices = p_shape->get_vertices();

		for (auto& elem : rotated_vertices)
			elem = physics::rotate_point(elem + p_shape->get_position(), transform);


		painter.draw_circle (transform.position + rotated_center, c_shape->get_radius(), color_);
		painter.draw_polygon(transform.position,                  rotated_vertices,      color_);
	}

	const std::shared_ptr<physics::RigidBody>& ComplexEntity::get_body() const
	{
		return body_;
	}
} // namespace game
