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

    ShapeAABB union_of(const ShapeAABB& aabb_A, const ShapeAABB& aabb_B);


    // Inline section
    inline bool ShapeAABB::collides(const ShapeAABB& aabb) const
    {
        if (this->max.x <= aabb.min.x || aabb.max.x <= this->min.x ||
            this->max.y <= aabb.min.y || aabb.max.y <= this->min.y)
        {
            return false;
        }

        return true;
    }

    inline void ShapeAABB::add_point(const Vector& point)
    {
        min.x = std::min(min.x, point.x);
        min.y = std::min(min.y, point.y);
        max.x = std::max(max.x, point.x);
        max.y = std::max(max.y, point.y);
    }

    inline void ShapeAABB::combine(const ShapeAABB& aabb)
    {
        add_point(aabb.min);
        add_point(aabb.max);
    }

    inline void ShapeAABB::move(const Vector& offset)
    {
        min += offset;
        max += offset;
    }

    inline void ShapeAABB::reset()
    {
        min = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
        max = { std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest() };
    }

    inline float ShapeAABB::get_perimeter() const
    {
        return ((max.x - min.x) + (max.y - min.y)) * 2.f;
    }

    inline bool ShapeAABB::is_valid() const
    {
        return min.x <= max.x && min.y <= max.y;
    }

    inline bool ShapeAABB::contains(const ShapeAABB& aabb) const
    {
        return
            aabb.max.x <= this->max.x &&
            aabb.max.y <= this->max.y &&
            aabb.min.x >= this->min.x &&
            aabb.min.y >= this->min.y;
    }

    inline bool ShapeAABB::cast_ray(const Ray& ray, RayHitInfo& output) const
    {
        float tmin = 0.f;
        float tmax = std::numeric_limits<float>::max();

        Vector normal;

        bool result = check_step(ray.direction.x, ray.origin.x, min.x, max.x, tmin, tmax, normal.x, normal.y);

        if (result == false)
            return false;

        result = check_step(ray.direction.y, ray.origin.y, min.y, max.y, tmin, tmax, normal.y, normal.x);

        if (result == false)
            return false;
        
        // Does the ray start inside the box?
        // Does the ray intersect beyond the max fraction?
        if (tmin > ray.max_fraction)
        {
            return false;
        }

        // Intersection.
        output.fraction = tmin;
        output.normal = normal;

        return true;
    }

    inline bool ShapeAABB::check_step(float ray_dir, float ray_origin, float aabb_min, float aabb_max, float& tmin, float& tmax, float& normal, float& normal_other) const
    {
        if (std::abs(ray_dir) < 0.00001f)
        {
            // Parallel.
            if (ray_origin < aabb_min || aabb_max < ray_origin)
            {
                return false;
            }
        }
        else
        {
            float inv_d = 1.0f / ray_dir;
            float t1 = (aabb_min - ray_origin) * inv_d;
            float t2 = (aabb_max - ray_origin) * inv_d;

            // Sign of the normal vector.
            float s = -1.0f;

            if (t1 > t2)
            {
                swap(t1, t2);
                s = 1.0f;
            }

            // Push the min up
            if (t1 > tmin)
            {
                normal_other = 0.f;
                normal = s;
                tmin = t1;
            }

            // Pull the max down
            tmax = fminf(tmax, t2);

            if (tmin > tmax)
            {
                return false;
            }
        }

        return true;
    }


    inline ShapeAABB union_of(const ShapeAABB& aabb_A, const ShapeAABB& aabb_B)
    {
        ShapeAABB AABB_C(aabb_A, aabb_B);

        return AABB_C;
    }
} // namespace physics
