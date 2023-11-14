#pragma once
#include <GameEngine/Game/Entities/Entity.h>
#include <GameEngine/PhysicsEngine/World.h>


namespace game
{
	class ComplexEntity : public Entity
	{
	public:
		ComplexEntity(std::shared_ptr<physics::World> world, const physics::Vector& position, float angle);
		~ComplexEntity();

		void render(graphics::Painter& painter) const override;
	};
} // namespace game
