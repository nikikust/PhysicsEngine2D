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

CircleShape CircleShape::generate_circle(const sf::Vector2u& window_size)
{
    // Radius
    int rad_start = 25, rad_end = 100;

    float radius = float(rand() % (rad_end - rad_start + 1) + rad_start);

    // Position
    sf::Vector2u pos_start = { 100, 100 }, pos_end = window_size - sf::Vector2u{ 100, 100 };

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
    return CircleShape{ radius, position, angle, mass };
}


void CircleShape::update_moment_of_inertia()
{
    moment_of_inertia_ = (float)PI2 * powf(radius_, 4);
}
