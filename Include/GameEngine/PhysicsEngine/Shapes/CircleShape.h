#pragma once
#include <GameEngine/PhysicsEngine/Shapes/Shape.h>


namespace physics
{
    class CircleShape : public Shape
    {
    public:
        CircleShape(float radius, const Vector& position);


        PhysicalData calculate_physical_data(float density) const override;
        bool cast_ray(const Ray& ray, const Transform& transform, RayHitInfo& output) const override;

        void  set_radius(float radius);
        float get_radius() const;

        static CircleShape generate_circle(const Vector& window_size);

    private:
        float radius_;
    };


    // Inline section
    inline void CircleShape::set_radius(float radius)
    {
        radius_ = radius;
    }

    inline float CircleShape::get_radius() const
    {
        return radius_;
    }
} // namespace physics
