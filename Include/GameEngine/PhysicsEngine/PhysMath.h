#pragma once
#include <GameEngine/Utils/Functions.h>


namespace physics
{
	struct Transform
	{
		sf::Vector2f position = {};
		float        angle    = 0;
	};

	struct PhysicalData
	{
		float area     = 0.0f;
		float mass     = 0.0f;
		float inv_mass = 0.0f;

		sf::Vector2f centroid = { 0.0f, 0.0f };

		float mmoi = 0.0f;
	};

	sf::Vector2f rotate_point         (const sf::Vector2f& point, const Transform& transform);
	sf::Vector2f rotate_and_move_point(const sf::Vector2f& point, const Transform& transform);

    float        triangle_area   (sf::Vector2f A, sf::Vector2f B);
    sf::Vector2f triangle_center (sf::Vector2f A, sf::Vector2f B);
    float        triangle_mmoi   (sf::Vector2f A, sf::Vector2f B, float triangle_mass);
} // namespace physics
