#pragma once
#include <GameEngine/PhysicsEngine/Shapes/Shape.h>


namespace physics
{
    class PolygonShape : public Shape
    {
    public:
        PolygonShape(const std::vector<Vector>& vertices, const Vector& position);


        PhysicalData calculate_physical_data(float density) const override;
        bool cast_ray(const Ray& ray, const Transform& transform, RayHitInfo& output) const override;

        void                             set_vertices(const std::vector<Vector>& vertices);
        const std::vector<Vector>& get_vertices() const;
        const std::vector<Vector>& get_normals() const;

        static PolygonShape generate_polygon(const Vector& window_size);

    private:
        std::vector<Vector> vertices_;
        std::vector<Vector> normals_;
    };
} // namespace physics

#include "PolygonShape.inl"
