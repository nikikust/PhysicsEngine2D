#pragma once
#include <GameEngine/Utils/Functions.h>


namespace physics
{
	class ShapeAABB
	{
	public:
		ShapeAABB();
		ShapeAABB(ShapeAABB&);
		ShapeAABB(const ShapeAABB&);
		ShapeAABB(const sf::Vector2f& min, const sf::Vector2f& max);
		ShapeAABB(const ShapeAABB& aabb_A, const ShapeAABB& aabb_B);

		/// Returns true if two AABBs collided
		bool collides(const ShapeAABB& aabb) const;

		/// Recalculates min and max points with new point
		void add_point(const sf::Vector2f& point);

		/// Combines two AABBs to cover both 
		void combine(const ShapeAABB& aabb);

		/// Move AABB to not to recalculate it
		void move(const sf::Vector2f& offset);

		/// Resets min and max to default values
		void reset();

		/// Returns perimeter of the AABB
		float get_perimeter() const;

		/// Returns true if min <= max
		bool is_valid() const;

		/// Returns true if this AABB contains provided AABB
		bool contains(const ShapeAABB& aabb) const;

		sf::Vector2f min;
		sf::Vector2f max;
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

    inline void ShapeAABB::add_point(const sf::Vector2f& point)
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

    inline void ShapeAABB::move(const sf::Vector2f& offset)
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


    inline ShapeAABB union_of(const ShapeAABB& aabb_A, const ShapeAABB& aabb_B)
    {
        ShapeAABB AABB_C(aabb_A, aabb_B);

        return AABB_C;
    }
} // namespace physics
