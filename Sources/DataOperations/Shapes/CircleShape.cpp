#include "../../../Include/DataOperations/Shapes/CircleShape.h"


CircleShape::CircleShape(float radius, const sf::Vector2f& position, float angle,
	                     const sf::Vector2f& linear_speed, float angular_speed, 
	                     float mass, bool fixed_x, bool fixed_y, bool fixed_angle)
	: Shape(position, angle, linear_speed, angular_speed, mass, fixed_x, fixed_y, fixed_angle), radius_(radius)
{
	update_moment_of_inertia();
}

// --- //

void CircleShape::update_moment_of_inertia()
{
	moment_of_inertia_ = (float)PI2 * powf(radius_, 4);
}
