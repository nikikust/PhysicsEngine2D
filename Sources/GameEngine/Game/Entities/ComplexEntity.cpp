#include <GameEngine/Game/Entities/ComplexEntity.h>


namespace game
{
	ComplexEntity::ComplexEntity(std::shared_ptr<physics::World> world, const physics::Vector& position, float angle)
		: Entity(sf::Color::Green)
	{
		auto circle_1 = new physics::CircleShape(
			50,      // Radius
			{50, -50} // Position
		);

		auto polygon_1 = new physics::PolygonShape(
			{ {-50, -50}, {50, -50}, {50, 50}, {-50, 50} }, // Vertices
			{50, 50} // Position
		);

		auto circle_2  = new physics::CircleShape(
			50,      // Radius
			{-50, 50} // Position
		);

		auto polygon_2 = new physics::PolygonShape(
			{ {-50, -50}, {50, -50}, {50, 50}, {-50, 50} }, // Vertices
			{-50, -50} // Position
		);

		main_body_->add_shape(circle_1) ->set_restitution(0.6f); // id: 0
		main_body_->add_shape(polygon_1)->set_restitution(0.6f); // id: 1
		main_body_->add_shape(circle_2) ->set_restitution(0.6f); // id: 2
		main_body_->add_shape(polygon_2)->set_restitution(0.6f); // id: 3

		main_body_->set_position(position);
		main_body_->set_angle(angle);

		world->add_body(main_body_);
	}

	ComplexEntity::~ComplexEntity()
	{
	}

	void ComplexEntity::render(graphics::Painter& painter) const
	{
		auto& transform = main_body_->get_transform();

		auto c_shape_1 = (physics::CircleShape *)(main_body_->get_fixtures().at(0)->get_shape());
		auto p_shape_1 = (physics::PolygonShape*)(main_body_->get_fixtures().at(1)->get_shape());
		auto c_shape_2 = (physics::CircleShape *)(main_body_->get_fixtures().at(2)->get_shape());
		auto p_shape_2 = (physics::PolygonShape*)(main_body_->get_fixtures().at(3)->get_shape());

		auto rotated_center_1 = physics::rotate_point(c_shape_1->get_position(), transform);
		auto rotated_center_2 = physics::rotate_point(c_shape_2->get_position(), transform);


		painter.draw_circle (utils::convert_to_sf(transform.position + rotated_center_1), c_shape_1->get_radius(), main_body_->get_angle(), color_);
		painter.draw_circle (utils::convert_to_sf(transform.position + rotated_center_2), c_shape_2->get_radius(), main_body_->get_angle(), color_);

		painter.draw_polygon(
			utils::convert_to_sf(transform.position), 
			utils::convert_to_sf(physics::rotate_polygon(p_shape_1->get_vertices(), p_shape_1->get_position(), transform)), 
			color_);
		painter.draw_polygon(
			utils::convert_to_sf(transform.position), 
			utils::convert_to_sf(physics::rotate_polygon(p_shape_2->get_vertices(), p_shape_2->get_position(), transform)), 
			color_);
	}
} // namespace game
