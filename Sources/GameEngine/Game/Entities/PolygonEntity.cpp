#include <GameEngine/Game/Entities/PolygonEntity.h>


namespace game
{
	PolygonEntity::PolygonEntity(std::shared_ptr<physics::World> world, const sf::Vector2f& position, float angle)
		: Entity(sf::Color::Red, new physics::RigidBody())
	{
		float half_size = 50;

		physics::PolygonShape polygon{
			{ {-half_size, -half_size}, { half_size, -half_size}, 
			  { half_size,  half_size}, {-half_size,  half_size} }, // Vertices
			{0, 0} // Position
		};

		main_body_->add_shape(polygon)->set_restitution(0.6f);

		main_body_->set_position(position);
		main_body_->set_angle(angle);

		world->add_body(main_body_);
	}

	PolygonEntity::~PolygonEntity()
	{
		free(main_body_);
	}


	void PolygonEntity::render(graphics::Painter& painter)
	{
		auto& transform = main_body_->get_transform();

		auto shape = std::dynamic_pointer_cast<physics::PolygonShape>(main_body_->get_fixtures().front()->get_shape());

		painter.draw_polygon(transform.position, physics::rotate_polygon(shape->get_vertices(), shape->get_position(), transform), color_);
	}
} // namespace game
