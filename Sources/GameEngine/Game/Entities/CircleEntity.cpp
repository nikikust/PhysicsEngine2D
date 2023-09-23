#include <GameEngine/Game/Entities/CircleEntity.h>


namespace game
{
	CircleEntity::CircleEntity(std::shared_ptr<physics::World> world, const sf::Vector2f& position, float angle)
		: Entity(sf::Color::Green)
	{
		physics::CircleShape circle{
			50,    // Radius
			{0, 0} // Position
		};

		physics::RigidBody body;

		body.add_shape(circle)->set_restitution(0.6f);

		body_ = world->add_body(body);

		body_->set_position(position);
		body_->set_angle(angle);
	}

	
	void CircleEntity::render(graphics::Painter& painter)
	{
		auto& transform = body_->get_transform();

		auto shape = std::dynamic_pointer_cast<physics::CircleShape>(body_->get_fixtures().front()->get_shape());

		auto rotated_center = physics::rotate_point(shape->get_position(), transform);

		painter.draw_circle(transform.position, shape->get_radius(), color_);
	}

	const std::shared_ptr<physics::RigidBody>& CircleEntity::get_body() const
	{
		return body_;
	}
} // namespace game
