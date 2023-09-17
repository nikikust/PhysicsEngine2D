#pragma once
#include "Shape.h"


class CircleShape : public Shape
{
public:
    CircleShape(float radius, const sf::Vector2f& position, float angle = 0, float mass = 1,
                const sf::Vector2f& linear_speed = { 0,0 }, float angular_speed = 0, 
                const sf::Vector2f& linear_acceleration = { 0,0 }, const sf::Vector2f& angular_acceleration = { 0,0 }, 
                const sf::Vector2f& force = { 0,0 },
                bool fixed_x = false, bool fixed_y = false, bool fixed_angle = false);

    void set_radius(float radius);

    float get_radius() const;

    static CircleShape generate_circle(const sf::Vector2u& window_size);

private:
    void update_moment_of_inertia();


    float radius_;
};
