#include "../../../Include/DataOperations/Shapes/CircleShape.h"


CircleShape::CircleShape(float radius, const sf::Vector2f& position, float angle,
	                     const sf::Vector2f& linear_speed, float angular_speed, 
	                     float mass, bool is_static)
	: Shape(position, angle, linear_speed, angular_speed, mass, is_static), radius_(radius)
{
}

// --- //

sf::Vector2f CircleShape::get_center_of_mass()
{
	return position_;
}
float CircleShape::get_moment_of_inertia()
{
	return (float)PI2 * powf(radius_, 4);
}
