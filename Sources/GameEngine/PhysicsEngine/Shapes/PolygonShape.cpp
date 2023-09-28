#include <GameEngine/PhysicsEngine/Shapes/PolygonShape.h>


namespace physics
{
    PolygonShape::PolygonShape(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& position)
        : Shape(ShapeType::Polygon, position), vertices_(vertices)
    {
    }

    // --- //

    PhysicalData PolygonShape::calculate_physical_data(float density) const
    {
        // Accumulate the following values
        float area = 0.0;
        float mass = 0.0;

        sf::Vector2f center = { 0.0, 0.0 };
        float mmoi = 0.0;

        // Take each vertex pair starting from the last-first vertex in order to consider all sides.
        auto count = (int32_t)vertices_.size();
        for (int32_t i = 0; i < count; ++i)
        {
            int32_t i_and_one = (i == count - 1) ? 0 : i + 1;
            sf::Vector2f A = vertices_.at(i);
            sf::Vector2f B = vertices_.at(i_and_one);

            float area_step = physics::triangle_area(A, B);
            float mass_step = density * area_step;
            sf::Vector2f center_step = physics::triangle_center(A, B);

            float mmoi_step = physics::triangle_mmoi(A, B, mass_step);

            area += area_step;
            center = (mass * center + mass_step * center_step) / (mass + mass_step);
            mass += mass_step;
            mmoi += mmoi_step;
        }

        // Transfer mass moment of inertia from the origin to the center of mass
        mmoi -= mass * utils::dot(center, center);

        return PhysicalData{ area, mass, (mass > 0.f) ? 1.f / mass : 0.f, center, mmoi };
    }

    void PolygonShape::set_vertices(const std::vector<sf::Vector2f>& vertices)
    {
        vertices_ = vertices;
    }
    const std::vector<sf::Vector2f>& PolygonShape::get_vertices() const
    {
        return vertices_;
    }

    PolygonShape PolygonShape::generate_polygon(const sf::Vector2u& window_size)
    {
        // Vertices
        int vert_start = 12, vert_end = 50;

        float half_width  = float(rand() % (vert_end - vert_start + 1) + vert_start);
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

        // Creation
        return PolygonShape{ vertices, position };
    }

} // namespace physics
