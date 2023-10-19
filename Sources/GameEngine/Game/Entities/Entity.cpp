#include <GameEngine/Game/Entities/Entity.h>


namespace game
{
	int32_t Entity::max_entity_id = 0;


	Entity::Entity(const sf::Color& color)
		: color_(color)
	{
		id_ = ++max_entity_id;

		main_body_ = new physics::RigidBody();
	}

	Entity::~Entity()
	{
		delete main_body_;
	}


	sf::Color Entity::get_color() const
	{
		return color_;
	}

	int32_t Entity::get_id() const
	{
		return id_;
	}

	physics::RigidBody* Entity::get_main_body()
	{
		return main_body_;
	}

	void Entity::set_color(const sf::Color& color)
	{
		color_ = color;
	}
} // namespace game
