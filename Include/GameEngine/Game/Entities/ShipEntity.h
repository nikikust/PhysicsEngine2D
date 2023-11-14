#pragma once
#include <GameEngine/Game/Entities/Entity.h>
#include <GameEngine/PhysicsEngine/World.h>


namespace game
{
	class ShipEntity : public Entity
	{
	public:
		ShipEntity(std::shared_ptr<physics::World> world, const physics::Vector& position, float angle, int32_t max_x, int32_t max_y);
		~ShipEntity();

		void render(graphics::Painter& painter) const override;
	};
} // namespace game
