#pragma once
#include <GameEngine/PhysicsEngine/Shapes/Shape.h>


namespace physics
{
    class CircleShape : public Shape
    {
    public:
        CircleShape(float radius, const sf::Vector2f& position);


        void  set_radius(float radius);
        float get_radius() const;

        static CircleShape generate_circle(const sf::Vector2u& window_size);

    private:
        void update_moment_of_inertia();


        float radius_;
    };
} // namespace physics
