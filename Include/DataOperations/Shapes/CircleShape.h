#pragma once
#include "Shape.h"


class CircleShape : public Shape
{
public:
	CircleShape(float radius, const sf::Vector2f& position, float angle = 0,
		        const sf::Vector2f& linear_speed = { 0,0 }, float angular_speed = 0, 
		        float mass = 1, bool fixed_x = false, bool fixed_y = false, bool fixed_angle = false);

private:
	void update_center_of_mass();
	void update_moment_of_inertia();


	float radius_;
};
