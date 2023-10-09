#include <GameEngine/Game/Entities/CircleEntity.h>


namespace game
{
	CircleEntity::CircleEntity(std::shared_ptr<physics::World> world, const sf::Vector2f& position, float angle)
		: Entity(sf::Color::Green, new physics::RigidBody())
	{
		physics::CircleShape circle{
			50,    // Radius
			{0, 0} // Position
		};

		main_body_->add_shape(circle)->set_restitution(0.6f);

		main_body_->set_position(position);
		main_body_->set_angle(angle);
		
		world->add_body(main_body_);
	}

	CircleEntity::~CircleEntity()
	{
		free(main_body_);
	}

	
	void CircleEntity::render(graphics::Painter& painter)
	{
		auto& transform = main_body_->get_transform();

		auto shape = std::dynamic_pointer_cast<physics::CircleShape>(main_body_->get_fixtures().front()->get_shape());

		auto rotated_center = physics::rotate_point(shape->get_position(), transform);

		painter.draw_circle(transform.position, shape->get_radius(), main_body_->get_angle(), color_);
	}
} // namespace game
