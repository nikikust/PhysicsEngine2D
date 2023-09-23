#include <GameEngine/PhysicsEngine/PhysMath.h>


namespace physics
{
	sf::Vector2f rotate_point(const sf::Vector2f& point, const Transform& transform)
	{
		return sf::Vector2f{
			point.x * cosf(transform.angle) - point.y * sinf(transform.angle),
			point.x * sinf(transform.angle) + point.y * cosf(transform.angle)
		};
	}

	sf::Vector2f rotate_and_move_point(const sf::Vector2f& point, const Transform& transform)
	{
		return transform.position + sf::Vector2f {
			point.x * cosf(transform.angle) - point.y * sinf(transform.angle),
			point.x * sinf(transform.angle) + point.y * cosf(transform.angle)
		};
	}
} // namespace physics
