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

    float        triangle_area   (sf::Vector2f A, sf::Vector2f B);
    sf::Vector2f triangle_center (sf::Vector2f A, sf::Vector2f B);
    float        triangle_mmoi   (sf::Vector2f A, sf::Vector2f B, float triangle_mass);
} // namespace physics
