#pragma once
#include "../../../Include/Utils/Functions.h"


class Shape
{
public:
	Shape(const sf::Vector2f& position, float angle = 0,
		  const sf::Vector2f& linear_speed = { 0,0 }, float angular_speed = 0,
		  float mass = 1, bool fixed_x = false, bool fixed_y = false, bool fixed_angle = false);

	virtual ~Shape() = default;

	sf::Vector2f get_center_of_mass();
	float        get_moment_of_inertia();

protected:
	virtual void update_moment_of_inertia() = 0;

	// --- Data

	sf::Vector2f position_;
	float        angle_;

	sf::Vector2f linear_speed_;
	float        angular_speed_;

	float        mass_;

	// --- Calculated values

	float        moment_of_inertia_;

	// --- Flags

	bool         fixed_x_;
	bool         fixed_y_;
	bool         fixed_angle_;
};
