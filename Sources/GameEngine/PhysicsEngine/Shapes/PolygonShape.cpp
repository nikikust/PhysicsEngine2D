#include <GameEngine/PhysicsEngine/Shapes/PolygonShape.h>


namespace physics
{
    PolygonShape::PolygonShape(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& position)
        : Shape(ShapeType::Rectangle, position), vertices_(vertices)
    {
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

        // Creation
        return PolygonShape{ vertices, position };
    }

} // namespace physics