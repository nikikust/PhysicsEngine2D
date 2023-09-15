#include "../../../Include/DataOperations/Shapes/Shape.h"


Shape::Shape(const sf::Vector2f& position, float angle,
		     const sf::Vector2f& linear_speed, float angular_speed,
		     float mass, bool fixed_x, bool fixed_y, bool fixed_angle)
	: position_(position), angle_(angle),
	  linear_speed_(linear_speed), angular_speed_(angular_speed), 
	  mass_(mass), fixed_x_(fixed_x), fixed_y_(fixed_y), fixed_angle_(fixed_angle)
{
	moment_of_inertia_ = 0 ;
}


sf::Vector2f Shape::get_center_of_mass()
{
	return position_;
}
float Shape::get_moment_of_inertia()
{
	return moment_of_inertia_;
}
