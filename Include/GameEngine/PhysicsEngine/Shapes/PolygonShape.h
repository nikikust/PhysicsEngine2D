#pragma once
#include <GameEngine/PhysicsEngine/Shapes/Shape.h>


namespace physics
{
    class PolygonShape : public Shape
    {
    public:
        PolygonShape(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& position);


        void                             set_vertices(const std::vector<sf::Vector2f>& vertices);
        const std::vector<sf::Vector2f>& get_vertices() const;

        static PolygonShape generate_rectangle(const sf::Vector2u& window_size);

    private:
        std::vector<sf::Vector2f> vertices_;
    };
} // namespace physics
