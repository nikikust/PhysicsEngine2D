#pragma once
#include <GameEngine/Game/Entities/Entity.h>
#include <GameEngine/PhysicsEngine/World.h>


namespace game
{
	class PolygonEntity : public Entity
	{
	public:
		PolygonEntity(std::shared_ptr<physics::World> world, const sf::Vector2f& position, float angle);
		~PolygonEntity();

		void render(graphics::Painter& painter) const override;
	};
} // namespace game
