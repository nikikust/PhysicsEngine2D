#pragma once
#include <GameEngine/Utils/Functions.h>
#include <GameEngine/GUIEngine/Painter.h>
#include <GameEngine/PhysicsEngine/RigidBody.h>


namespace game
{
	class Entity
	{
	public:
		Entity(const sf::Color& color = sf::Color::White);

		void      set_color(const sf::Color& color);
		sf::Color get_color() const;

		int32_t get_id() const;

		virtual void render(graphics::Painter& painter) = 0;

	protected:
		sf::Color color_;

		

		// --- //

		int32_t id_;

		static int32_t max_entity_id;
	};
} // namespace game
