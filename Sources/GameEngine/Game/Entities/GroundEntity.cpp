#include <GameEngine/Game/Entities/GroundEntity.h>


namespace game
{
	GroundEntity::GroundEntity(std::shared_ptr<physics::World> world, const sf::Vector2f& position, float angle)
		: Entity({ 127, 127, 127 })
	{
		std::vector<sf::Vector2f> base_vector{ {-700, -25}, {700, -25}, {700, 25}, {-700, 25} };
		std::vector<sf::Vector2f> vector_1, vector_2;

		for (int32_t i = 0; i < 4; ++i)
		{
			vector_1.push_back(utils::rotate_point(base_vector.at(i),  (float)PI2 / 7.f));
			vector_2.push_back(utils::rotate_point(base_vector.at(i), -(float)PI2 / 7.f));
		}

		physics::PolygonShape polygon_1{
			vector_1, // Vertices
			{-600, 0}    // Position
		};
		physics::PolygonShape polygon_2{
			vector_2, // Vertices
			{ 600, 0}    // Position
		};

		physics::RigidBody body;

		body.add_shape(polygon_1)->set_restitution(0.6f);
		body.add_shape(polygon_2)->set_restitution(0.6f);


		body_ = world->add_body(body);

		body_->set_position(position)
			  .set_angle(angle)
			  .set_angular_fixation(true)
			  .set_linear_fixation(true, true);
	}


	void GroundEntity::render(graphics::Painter& painter)
	{
		auto& transform = body_->get_transform();

		auto shape_1 = std::dynamic_pointer_cast<physics::PolygonShape>(body_->get_fixtures().at(0)->get_shape());
		auto shape_2 = std::dynamic_pointer_cast<physics::PolygonShape>(body_->get_fixtures().at(1)->get_shape());

		auto rotated_vertices_1 = shape_1->get_vertices();
		auto rotated_vertices_2 = shape_2->get_vertices();

		for (auto& elem : rotated_vertices_1)
			elem = physics::rotate_point(elem + shape_1->get_position(), transform);
		for (auto& elem : rotated_vertices_2)
			elem = physics::rotate_point(elem + shape_2->get_position(), transform);

		painter.draw_polygon(transform.position, rotated_vertices_1, color_);
		painter.draw_polygon(transform.position, rotated_vertices_2, color_);
	}

	const std::shared_ptr<physics::RigidBody>& GroundEntity::get_body() const
	{
		return body_;
	}
} // namespace game
