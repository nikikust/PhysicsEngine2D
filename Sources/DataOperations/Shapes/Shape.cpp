#include "../../../Include/DataOperations/Shapes/Shape.h"


Shape::Shape(const sf::Vector2f& position, float angle,
		     const sf::Vector2f& linear_speed, float angular_speed,
		     float mass, bool is_static)
	: position_(position), angle_(angle),
	  linear_speed_(linear_speed), angular_speed_(angular_speed), 
	  mass_(mass), is_static_(is_static)
{
}
