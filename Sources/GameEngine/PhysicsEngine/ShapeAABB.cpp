#include <GameEngine/PhysicsEngine/ShapeAABB.h>


namespace physics
{
    ShapeAABB::ShapeAABB()
        : min({ std::numeric_limits<float>::max   (), std::numeric_limits<float>::max   () }),
          max({ std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest() }) {}

    ShapeAABB::ShapeAABB(ShapeAABB& shape)
    {
        this->min = shape.min;
        this->max = shape.max;
    }

    ShapeAABB::ShapeAABB(const ShapeAABB& shape)
    {
        this->min = shape.min;
        this->max = shape.max;
    }

    ShapeAABB::ShapeAABB(const sf::Vector2f& min, const sf::Vector2f& max)
        : min(min), max(max) {}

    ShapeAABB::ShapeAABB(const ShapeAABB& aabb_A, const ShapeAABB& aabb_B)
    {
        min.x = std::min(aabb_A.min.x, aabb_B.min.x);
        min.y = std::min(aabb_A.min.y, aabb_B.min.y);
        max.x = std::max(aabb_A.max.x, aabb_B.max.x);
        max.y = std::max(aabb_A.max.y, aabb_B.max.y);
    }


    bool ShapeAABB::collides(const ShapeAABB& aabb) const
    {
        if (this->max.x <= aabb.min.x || aabb.max.x <= this->min.x ||
            this->max.y <= aabb.min.y || aabb.max.y <= this->min.y)
        {
            return false;
        }

        return true;
    }
    
    void ShapeAABB::add_point(const sf::Vector2f& point)
    {
        min.x = std::min(min.x, point.x);
        min.y = std::min(min.y, point.y);
        max.x = std::max(max.x, point.x);
        max.y = std::max(max.y, point.y);
    }
    
    void ShapeAABB::combine(const ShapeAABB& aabb)
    {
        add_point(aabb.min);
        add_point(aabb.max);
    }

    void ShapeAABB::move(const sf::Vector2f& offset)
    {
        min += offset;
        max += offset;
    }

    void ShapeAABB::reset()
    {
        min = { std::numeric_limits<float>::max   (), std::numeric_limits<float>::max   () };
        max = { std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest() };
    }

    float ShapeAABB::get_perimeter() const
    {
        return ((max.x - min.x) + (max.y - min.y)) * 2.f;
    }

    bool ShapeAABB::is_valid() const
    {
        return min.x <= max.x && min.y <= max.y;
    }

    bool ShapeAABB::contains(const ShapeAABB& aabb) const
    {
        return 
            aabb.max.x <= this->max.x &&
            aabb.max.y <= this->max.y &&
            aabb.min.x >= this->min.x &&
            aabb.min.y >= this->min.y;
    }


    ShapeAABB union_of(const ShapeAABB& aabb_A, const ShapeAABB& aabb_B)
    {
        ShapeAABB AABB_C(aabb_A, aabb_B);

        return AABB_C;
    }
} // namespace physics
