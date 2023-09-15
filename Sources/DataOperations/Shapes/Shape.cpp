#include "../../../Include/DataOperations/Shapes/Shape.h"


Shape::Shape(ShapeType shape_type, const sf::Vector2f& position, float angle,
             const sf::Vector2f& linear_speed, float angular_speed,
             float mass, bool fixed_x, bool fixed_y, bool fixed_angle)
    : position_(position), angle_(angle),
      linear_speed_(linear_speed), angular_speed_(angular_speed), 
      mass_(mass), fixed_x_(fixed_x), fixed_y_(fixed_y), fixed_angle_(fixed_angle), shape_type_(shape_type)
{
    moment_of_inertia_ = 0 ;
}


sf::Vector2f Shape::get_center_of_mass() const
{
    return position_;
}
float Shape::get_moment_of_inertia() const
{
    return moment_of_inertia_;
}

void Shape::set_position(const sf::Vector2f& position)
{
    position_ = position;
}
void Shape::set_angle(float angle)
{
    angle_ = angle;
}
void Shape::set_linear_speed(const sf::Vector2f& linear_speed)
{
    linear_speed_ = linear_speed;
}
void Shape::set_angular_speed(float angular_speed)
{
    angular_speed_ = angular_speed;
}
void Shape::set_mass(float mass)
{
    mass_ = mass;
}

sf::Vector2f Shape::get_position() const
{
    return position_;
}
float Shape::get_angle() const
{
    return angle_;
}
sf::Vector2f Shape::get_linear_speed() const
{
    return linear_speed_;
}
float Shape::get_angular_speed() const
{
    return angular_speed_;
}
float Shape::get_mass() const
{
    return mass_;
}
ShapeType Shape::get_shape() const
{
    return shape_type_;
}

void Shape::move(const sf::Vector2f& delta)
{
    position_ += delta;
}
void Shape::rotate(float angle)
{
    angle_ += angle;
}
