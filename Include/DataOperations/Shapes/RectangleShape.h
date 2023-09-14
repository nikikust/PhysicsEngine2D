#pragma once
#include "Shape.h"


class RectangleShape : public Shape
{
public:
	RectangleShape(const sf::Vector2f& size, const sf::Vector2f& position, float angle = 0,
		           const sf::Vector2f& linear_speed = { 0,0 }, float angular_speed = 0, 
		           float mass = 1, bool is_static = false);

	sf::Vector2f get_center_of_mass();
	float        get_moment_of_inertia();

private:
	sf::Vector2f size_;
};
