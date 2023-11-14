#pragma once
#include <GameEngine/PhysicsEngine/Callbacks/RayCastCallback.h>
#include <GameEngine/PhysicsEngine/Fixture.h>
#include <GameEngine/Utils/Functions.h>


namespace game
{
	class ClosestRayHit : public physics::RayCastCallback
	{
	public:
		ClosestRayHit(const physics::Ray& ray);

	public:
		void report_fixture(physics::Fixture* fixture, physics::RayHitInfo output) override;

		bool is_hit() const;

		sf::Vector2f get_touch_point() const;
		const sf::Vector2f& get_normal() const;

	private:
		const physics::Ray ray_;

		bool is_hit_;

		float closest_t_;
		sf::Vector2f normal_;
	};


	// Inline section
	inline bool ClosestRayHit::is_hit() const
	{
		return is_hit_;
	}

	inline sf::Vector2f ClosestRayHit::get_touch_point() const
	{
		return closest_t_ * utils::convert_to_sf(ray_.direction + ray_.origin);
	}

	inline const sf::Vector2f& ClosestRayHit::get_normal() const
	{
		return normal_;
	}

} // namespace game
