#pragma once
#include <GameEngine/Game/Entities/Entity.h>
#include <GameEngine/PhysicsEngine/World.h>


namespace game
{
	class ComplexEntity : public Entity
	{
	public:
		ComplexEntity(std::shared_ptr<physics::World> world, const sf::Vector2f& position, float angle);

		void render(graphics::Painter& painter) override;

		const std::shared_ptr<physics::RigidBody>& get_body() const;

	private:
		std::shared_ptr<physics::RigidBody> body_;
	};
} // namespace game
