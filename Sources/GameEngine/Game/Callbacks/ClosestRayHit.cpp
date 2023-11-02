#include <GameEngine/Game/Callbacks/ClosestRayHit.h>


namespace game
{
	ClosestRayHit::ClosestRayHit(const physics::Ray& ray)
		: ray_(ray), is_hit_(false), closest_t_(ray.max_fraction), normal_() {}


	void ClosestRayHit::report_fixture(physics::Fixture* fixture, physics::RayHitInfo output)
	{
		if (output.fraction <= closest_t_)
		{
			closest_t_ = output.fraction;
			normal_    = output.normal;

			is_hit_ = true;
		}
	}
} // namespace game
