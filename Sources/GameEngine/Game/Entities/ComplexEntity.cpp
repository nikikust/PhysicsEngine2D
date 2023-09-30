#include <GameEngine/Game/Entities/ComplexEntity.h>


namespace game
{
	ComplexEntity::ComplexEntity(std::shared_ptr<physics::World> world, const sf::Vector2f& position, float angle)
		: Entity(sf::Color::Green)
	{
		physics::RigidBody body;

		physics::CircleShape circle_1{
			50,      // Radius
			{50, -50} // Position
		};

		physics::PolygonShape polygon_1{
			{ {-50, -50}, {50, -50}, {50, 50}, {-50, 50} }, // Vertices
			{50, 50} // Position
		};

		physics::CircleShape circle_2{
			50,      // Radius
			{-50, 50} // Position
		};

		physics::PolygonShape polygon_2{
			{ {-50, -50}, {50, -50}, {50, 50}, {-50, 50} }, // Vertices
			{-50, -50} // Position
		};

		body.add_shape(circle_1) ->set_restitution(0.6f); // id: 0
		body.add_shape(polygon_1)->set_restitution(0.6f); // id: 1
		body.add_shape(circle_2) ->set_restitution(0.6f); // id: 2
		body.add_shape(polygon_2)->set_restitution(0.6f); // id: 3

		body_ = world->add_body(body);

		body_->set_position(position);
		body_->set_angle(angle);
	}


	void ComplexEntity::render(graphics::Painter& painter)
	{
		auto& transform = body_->get_transform();

		auto c_shape_1 = std::dynamic_pointer_cast<physics::CircleShape> (body_->get_fixtures().at(0)->get_shape());
		auto p_shape_1 = std::dynamic_pointer_cast<physics::PolygonShape>(body_->get_fixtures().at(1)->get_shape());
		auto c_shape_2 = std::dynamic_pointer_cast<physics::CircleShape> (body_->get_fixtures().at(2)->get_shape());
		auto p_shape_2 = std::dynamic_pointer_cast<physics::PolygonShape>(body_->get_fixtures().at(3)->get_shape());

		auto rotated_center_1 = physics::rotate_point(c_shape_1->get_position(), transform);
		auto rotated_center_2 = physics::rotate_point(c_shape_2->get_position(), transform);

		painter.draw_circle (transform.position + rotated_center_1, c_shape_1->get_radius(), body_->get_angle(),                           color_);
		painter.draw_polygon(transform.position, physics::rotate_polygon(p_shape_1->get_vertices(), p_shape_1->get_position(), transform), color_);
		painter.draw_circle (transform.position + rotated_center_2, c_shape_2->get_radius(), body_->get_angle(),                           color_);
		painter.draw_polygon(transform.position, physics::rotate_polygon(p_shape_2->get_vertices(), p_shape_2->get_position(), transform), color_);
	}

	const std::shared_ptr<physics::RigidBody>& ComplexEntity::get_body() const
	{
		return body_;
	}
} // namespace game
