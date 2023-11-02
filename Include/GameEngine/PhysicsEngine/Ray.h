#pragma once
#include <GameEngine/Utils/Functions.h>


namespace physics
{
	struct Ray
	{
		sf::Vector2f origin;
		sf::Vector2f direction;

		float max_fraction = 100000.f;
	};

	struct RayHitInfo
	{
		float fraction;

		sf::Vector2f normal;
	};
} // namespace physics
