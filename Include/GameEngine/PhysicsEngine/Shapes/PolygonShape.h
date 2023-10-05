#pragma once
#include <GameEngine/PhysicsEngine/Shapes/Shape.h>


namespace physics
{
    class PolygonShape : public Shape
    {
    public:
        PolygonShape(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& position);


        PhysicalData calculate_physical_data(float density) const override;

        void                             set_vertices(const std::vector<sf::Vector2f>& vertices);
        const std::vector<sf::Vector2f>& get_vertices() const;

        static PolygonShape generate_polygon(const sf::Vector2u& window_size);

    private:
        std::vector<sf::Vector2f> vertices_;
    };


    // Inline section
    inline void PolygonShape::set_vertices(const std::vector<sf::Vector2f>& vertices)
    {
        vertices_ = vertices;
    }

    inline const std::vector<sf::Vector2f>& PolygonShape::get_vertices() const
    {
        return vertices_;
    }
} // namespace physics
