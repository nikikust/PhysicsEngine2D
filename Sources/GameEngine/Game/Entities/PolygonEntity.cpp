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

		body_->set_position(position);
		body_->set_angle(angle);
	}


	void PolygonEntity::render(graphics::Painter& painter)
	{
		auto& transform = body_->get_transform();

		auto shape = std::dynamic_pointer_cast<physics::PolygonShape>(body_->get_fixtures().front()->get_shape());

		painter.draw_polygon(transform.position, physics::rotate_polygon(shape->get_vertices(), shape->get_position(), transform), color_);
	}

	const std::shared_ptr<physics::RigidBody>& PolygonEntity::get_body() const
	{
		return body_;
	}
} // namespace game
