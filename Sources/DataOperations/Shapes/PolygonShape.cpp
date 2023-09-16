#include "../../../Include/DataOperations/Shapes/PolygonShape.h"


PolygonShape::PolygonShape(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& position, float angle,
                           const sf::Vector2f& linear_speed, float angular_speed, 
                           float mass, bool fixed_x, bool fixed_y, bool fixed_angle)
    : Shape(ShapeType::Rectangle, position, angle, linear_speed,angular_speed, mass, fixed_x, fixed_y, fixed_angle),
      vertices_(vertices)
{
    update_moment_of_inertia();
}

// --- //

void PolygonShape::set_vertices(const std::vector<sf::Vector2f>& vertices)
{
    vertices_ = vertices;
}

const std::vector<sf::Vector2f>& PolygonShape::get_vertices() const
{
    return vertices_;
}

void PolygonShape::update_moment_of_inertia()
{
    moment_of_inertia_ = 1; // (mass_ * size_.x * size_.x * size_.y * size_.y) / 12.f;
}
