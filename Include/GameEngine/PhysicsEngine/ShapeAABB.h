#pragma once
#include <GameEngine/PhysicsEngine/PhysMath.h>
#include <GameEngine/PhysicsEngine/Ray.h>


namespace physics
{
    class ShapeAABB
    {
    public:
        ShapeAABB();
        ShapeAABB(ShapeAABB&);
        ShapeAABB(const ShapeAABB&);
        ShapeAABB(const Vector& min, const Vector& max);
        ShapeAABB(const ShapeAABB& aabb_A, const ShapeAABB& aabb_B);

        /// Returns true if two AABBs collided
        bool collides(const ShapeAABB& aabb) const;

        /// Recalculates min and max points with new point
        void add_point(const Vector& point);

        /// Combines two AABBs to cover both 
        void combine(const ShapeAABB& aabb);

        /// Move AABB to not to recalculate it
        void move(const Vector& offset);

        /// Resets min and max to default values
        void reset();

        /// Returns perimeter of the AABB
        float get_perimeter() const;

        /// Returns true if min <= max
        bool is_valid() const;

        /// Returns true if this AABB contains provided AABB
        bool contains(const ShapeAABB& aabb) const;

        ///  Checks intersection between AABB and ray
        bool cast_ray(const Ray& ray, RayHitInfo& output) const;

        Vector min;
        Vector max;

    private:
        bool check_step(float ray_dir, float ray_origin, float aabb_min, float aabb_max, float& tmin, float& tmax, float& normal, float& normal_other) const;
    };
} // namespace physics

#include "ShapeAABB.inl"
