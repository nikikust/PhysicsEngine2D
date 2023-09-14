#pragma once
#include "../../../Include/Utils/Functions.h"


class Shape
{
public:
	Shape(const sf::Vector2f& position, float angle = 0,
		  const sf::Vector2f& linear_speed = { 0,0 }, float angular_speed = 0,
		  float mass = 1, bool is_static = false);

	virtual ~Shape() = default;

protected:
	sf::Vector2f position_;
	float        angle_;

	sf::Vector2f linear_speed_;
	float        angular_speed_;

	float        mass_;

	bool         is_static_;
};
