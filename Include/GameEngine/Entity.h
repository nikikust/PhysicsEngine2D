#pragma once
#include <GameEngine/Utils/Functions.h>
#include <GameEngine/PhysicsEngine/RigidBody.h>


namespace game
{
	class Entity
	{
	public:
		Entity(const sf::Color& color = sf::Color::White);

		void      set_color(const sf::Color& color);
		sf::Color get_color() const;

	protected:
		sf::Color color_;

		

		// --- //

		int32_t id_;

		static int32_t max_entity_id;
	};
} // namespace game