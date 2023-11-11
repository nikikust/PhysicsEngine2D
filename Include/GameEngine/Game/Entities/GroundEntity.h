#pragma once
#include <GameEngine/Game/Entities/Entity.h>
#include <GameEngine/PhysicsEngine/World.h>


namespace game
{
	class GroundEntity : public Entity
	{
	public:
		GroundEntity(std::shared_ptr<physics::World> world, const physics::Vector& position, float angle);
		~GroundEntity();

		void render(graphics::Painter& painter) const override;
	};
} // namespace game
