#include <GameEngine/PhysicsEngine/Shapes/CircleShape.h>


namespace physics
{
    CircleShape::CircleShape(float radius, const sf::Vector2f& position)
        : Shape(ShapeType::Circle, position), radius_(radius)
    {
    }

    // --- //

    PhysicalData CircleShape::calculate_physical_data(float density) const
    {
        float area = PIf * radius_ * radius_;
        float mass = area * density;
        float mmoi = PI4f * powf(radius_, 4);

        return { area , mass, (mass > 0.f) ? 1.f / mass : 0.f, {}, mmoi };
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

        // Creation
        return CircleShape{ radius, position };
    }

} // namespace physics