#pragma once
#include <GameEngine/PhysicsEngine/Ray.h>


namespace physics
{
	class Fixture;

	class RayCastCallback
	{
	public:
		virtual ~RayCastCallback() = default;

		virtual void report_fixture(Fixture* fixture, RayHitInfo output) = 0;
	};
} // namespace physics
