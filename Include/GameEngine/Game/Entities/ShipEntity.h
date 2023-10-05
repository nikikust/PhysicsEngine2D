#pragma once
#include <GameEngine/Game/Entities/Entity.h>
#include <GameEngine/PhysicsEngine/World.h>


namespace game
{
	class ShipEntity : public Entity
	{
	public:
		ShipEntity(std::shared_ptr<physics::World> world, const sf::Vector2f& position, float angle);

		void render(graphics::Painter& painter) override;
	};
} // namespace game
