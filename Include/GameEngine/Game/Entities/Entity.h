#pragma once
#include <GameEngine/Utils/Functions.h>
#include <GameEngine/GUIEngine/Painter.h>
#include <GameEngine/PhysicsEngine/RigidBody.h>


namespace game
{
	class Entity
	{
	public:
		Entity(const sf::Color& color, std::shared_ptr<physics::RigidBody> main_body);

		void      set_color(const sf::Color& color);
		sf::Color get_color() const;

		int32_t get_id() const;

		virtual void render(graphics::Painter& painter) = 0;

		std::shared_ptr<physics::RigidBody>& get_main_body();

	protected:
		sf::Color color_;

		std::shared_ptr<physics::RigidBody> main_body_;

		// --- //

		int32_t id_;

		static int32_t max_entity_id;
	};
} // namespace game
