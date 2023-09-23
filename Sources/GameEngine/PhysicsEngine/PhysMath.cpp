#include <GameEngine/PhysicsEngine/PhysMath.h>


namespace physics
{
	sf::Vector2f rotate_point(const sf::Vector2f& point, const Transform& transform)
	{
		auto shifted_point = point - transform.centroid;

		return transform.centroid + sf::Vector2f{
			shifted_point.x * cosf(transform.angle) - shifted_point.y * sinf(transform.angle),
			shifted_point.x * sinf(transform.angle) + shifted_point.y * cosf(transform.angle)
		};
	}

	sf::Vector2f rotate_and_move_point(const sf::Vector2f& point, const Transform& transform)
	{
		auto shifted_point = point - transform.centroid;

		return transform.position + transform.centroid + sf::Vector2f {
			shifted_point.x * cosf(transform.angle) - shifted_point.y * sinf(transform.angle),
			shifted_point.x * sinf(transform.angle) + shifted_point.y * cosf(transform.angle)
		};
	}

	float triangle_area(sf::Vector2f A, sf::Vector2f B)
	{
		return utils::cross(A, B) / 2.f;
	}
	sf::Vector2f triangle_center(sf::Vector2f A, sf::Vector2f B)
	{
		return (A + B) / 3.f;
	}
	float triangle_mmoi(sf::Vector2f A, sf::Vector2f B, float triangle_mass)
	{
		return triangle_mass / 6.f * (utils::dot(A, A) + utils::dot(B, B) + utils::dot(A, B));
	}
} // namespace physics
