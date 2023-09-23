#include <GameEngine/Game/Entities/PolygonEntity.h>


namespace game
{
	PolygonEntity::PolygonEntity(std::shared_ptr<physics::World> world, const sf::Vector2f& position, float angle)
		: Entity(sf::Color::Red)
	{
		physics::PolygonShape polygon{
			{ {-50, -50}, {50, -50}, {50, 50}, {-50, 50} }, // Vertices
			{0, 0} // Position
		};

		physics::RigidBody body;

		body.add_shape(polygon)->set_restitution(0.6f);

		body_ = world->add_body(body);
		body_->set_transform({ position, angle });
	}


	void PolygonEntity::render(graphics::Painter& painter)
	{
		auto& transform = body_->get_transform();

		auto shape = std::dynamic_pointer_cast<physics::PolygonShape>(body_->get_fixtures().front()->get_shape());

		auto rotated_vertices = shape->get_vertices();

		for (auto& elem : rotated_vertices)
			elem = physics::rotate_point(elem + shape->get_position(), transform);

		painter.draw_polygon(transform.position, rotated_vertices, color_);
	}

	const std::shared_ptr<physics::RigidBody>& PolygonEntity::get_body() const
	{
		return body_;
	}
} // namespace game
