#pragma once
#include <GameEngine/Utils/Functions.h>


namespace physics
{
	struct Transform
	{
		sf::Vector2f position;
		float        angle;
	};

	sf::Vector2f rotate_point         (const sf::Vector2f& point, const Transform& transform);
	sf::Vector2f rotate_and_move_point(const sf::Vector2f& point, const Transform& transform);
} // namespace physics
