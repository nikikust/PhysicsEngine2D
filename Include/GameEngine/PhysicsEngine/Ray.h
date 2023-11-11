#pragma once
#include <GameEngine/PhysicsEngine/PhysMath.h>


namespace physics
{
	struct Ray
	{
		Vector origin;
		Vector direction;

		float max_fraction = 100000.f;
	};

	struct RayHitInfo
	{
		float fraction;

		Vector normal;
	};
} // namespace physics
