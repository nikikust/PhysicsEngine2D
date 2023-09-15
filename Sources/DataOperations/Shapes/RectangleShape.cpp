#include "../../../Include/DataOperations/Shapes/RectangleShape.h"


RectangleShape::RectangleShape(const sf::Vector2f& size, const sf::Vector2f& position, float angle,
                               const sf::Vector2f& linear_speed, float angular_speed, 
                               float mass, bool fixed_x, bool fixed_y, bool fixed_angle)
    : Shape(ShapeType::Rectangle, position, angle, linear_speed,angular_speed, mass, fixed_x, fixed_y, fixed_angle),
      size_(size)
{
    update_moment_of_inertia();
}

// --- //

void RectangleShape::set_size(const sf::Vector2f& size)
{
    size_ = size;
}

sf::Vector2f RectangleShape::get_size() const
{
    return size_;
}

void RectangleShape::update_moment_of_inertia()
{
    moment_of_inertia_ = (mass_ * size_.x * size_.x * size_.y * size_.y) / 12.f;
}
