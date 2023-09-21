#pragma once
#include <GameEngine/Utils/Functions.h>


namespace physics
{
	struct Transform
	{
		sf::Vector2f position;
		float        angle;
	};

	sf::Vector2f rotate_point(const sf::Vector2f& point, Transform transform);
} // namespace physics
