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
} // namespace physics
