#include "../../../Include/DataOperations/Shapes/RectangleShape.h"


RectangleShape::RectangleShape(const sf::Vector2f& size, const sf::Vector2f& position, float angle,
	                           const sf::Vector2f& linear_speed, float angular_speed, 
	                           float mass, bool is_static)
	: Shape(position, angle, linear_speed,angular_speed, mass, is_static), size_(size)
{
}

// --- //

sf::Vector2f RectangleShape::get_center_of_mass()
{
	return position_;
}
float RectangleShape::get_moment_of_inertia()
{
	return (mass_ * size_.x * size_.x * size_.y * size_.y) / 12.f;
}
