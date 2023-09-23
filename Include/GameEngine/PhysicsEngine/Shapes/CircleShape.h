#pragma once
#include <GameEngine/PhysicsEngine/Shapes/Shape.h>


namespace physics
{
    class CircleShape : public Shape
    {
    public:
        CircleShape(float radius, const sf::Vector2f& position);


        sf::Vector2f get_centroid          ()              const override;
        float        get_moment_of_inertia (float density) const override;

        void  set_radius(float radius);
        float get_radius() const;

        static CircleShape generate_circle(const sf::Vector2u& window_size);

    private:
        float radius_;
    };
} // namespace physics
