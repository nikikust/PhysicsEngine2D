#pragma once
#include <GameEngine/Game/Entities/Entity.h>
#include <GameEngine/PhysicsEngine/World.h>


namespace game
{
	class CircleEntity : public Entity
	{
	public:
		CircleEntity(std::shared_ptr<physics::World> world, const sf::Vector2f& position, float angle);
		~CircleEntity();

		void render(graphics::Painter& painter) override;
	};
} // namespace game
