#include "../../../Include/DataOperations/Shapes/CircleShape.h"


CircleShape::CircleShape(float radius, const sf::Vector2f& position, float angle, float mass,
                         const sf::Vector2f& linear_speed, float angular_speed,
                         const sf::Vector2f& linear_acceleration, const sf::Vector2f& angular_acceleration, 
                         const sf::Vector2f& force,
                         bool fixed_x, bool fixed_y, bool fixed_angle)
    : Shape(ShapeType::Circle, position, angle, mass, linear_speed, angular_speed,
            linear_acceleration, angular_acceleration, force, fixed_x, fixed_y, fixed_angle),
      radius_(radius)
{
    update_moment_of_inertia();
}

// --- //

void CircleShape::set_radius(float radius)
{
    radius_ = radius;
}

float CircleShape::get_radius() const
{
    return radius_;
}


void CircleShape::update_moment_of_inertia()
{
    moment_of_inertia_ = (float)PI2 * powf(radius_, 4);
}
