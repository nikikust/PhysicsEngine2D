#pragma once
#include "Shape.h"


class CircleShape : public Shape
{
public:
    CircleShape(float radius, const sf::Vector2f& position, float angle = 0,
                const sf::Vector2f& linear_speed = { 0,0 }, float angular_speed = 0, 
                float mass = 1, bool fixed_x = false, bool fixed_y = false, bool fixed_angle = false);

    void set_radius(float radius);

    float get_radius() const;

private:
    void update_moment_of_inertia();


    float radius_;
};
