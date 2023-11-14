#pragma once
#include <GameEngine/PhysicsEngine/PhysMath.h>
#include <GameEngine/PhysicsEngine/Ray.h>
#include <GameEngine/PhysicsEngine/PhysMath.h>


namespace physics
{
    enum ShapeType
    {
        Polygon = 0,
        Circle    = 1
    };

    class Shape
    {
    public:
        Shape(ShapeType shape_type, const Vector& position);

        virtual ~Shape() = default;


        // --- //
        virtual PhysicalData calculate_physical_data(float density) const = 0;
        virtual bool cast_ray(const Ray& ray, const Transform& transform, RayHitInfo& output) const = 0;

        // --- Fields manipulations

        Vector get_position () const;
        void         set_position (const Vector& position);

        ShapeType get_shape () const;
        int32_t   get_id    () const;

    protected:

        // --- Shape info
        ShapeType shape_type_;
        int32_t   id_;

        Vector position_;

        // --- Config
        static int32_t      max_object_id;
    };
} // namespace physics

#include "Shape.inl"
