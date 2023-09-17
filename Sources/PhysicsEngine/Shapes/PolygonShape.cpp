#include "../../../Include/PhysicsEngine/Shapes/PolygonShape.h"


PolygonShape::PolygonShape(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& position, float angle, float mass,
                           const sf::Vector2f& linear_speed, float angular_speed,
                           const sf::Vector2f& linear_acceleration, const sf::Vector2f& angular_acceleration,
                           const sf::Vector2f& force,
                           bool fixed_x, bool fixed_y, bool fixed_angle)
    : Shape(ShapeType::Rectangle, position, angle, mass, linear_speed, angular_speed,
            linear_acceleration, angular_acceleration, force, fixed_x, fixed_y, fixed_angle),
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

PolygonShape PolygonShape::generate_rectangle(const sf::Vector2u& window_size)
{
    // Vertices
    int vert_start = 12, vert_end = 50;

    float half_width = float(rand() % (vert_end - vert_start + 1) + vert_start);
    float half_heigth = float(rand() % (vert_end - vert_start + 1) + vert_start);

    std::vector<sf::Vector2f> vertices{
        { -half_width, -half_heigth },
        {  half_width, -half_heigth },
        {  half_width,  half_heigth },
        { -half_width,  half_heigth }
    };

    // Position
    sf::Vector2u pos_start = { 50, 50 }, pos_end = window_size - sf::Vector2u{ 50, 50 };

    sf::Vector2f position = {
        float(rand() % (pos_end.x - pos_start.x + 1) + pos_start.x),
        float(rand() % (pos_end.y - pos_start.y + 1) + pos_start.y)
    };

    // Angle
    int ang_start = 0, ang_end = 314;

    float angle = (rand() % (ang_end - ang_start + 1) + ang_start) / 100.f;

    // Mass
    int mass_start = 500, mass_end = 1500;

    float mass = float(rand() % (mass_end - mass_start + 1) + mass_start);

    // Creation
    return PolygonShape{ vertices, position, angle, mass };
}


void PolygonShape::update_moment_of_inertia()
{
    moment_of_inertia_ = 1; // (mass_ * size_.x * size_.x * size_.y * size_.y) / 12.f;
}
