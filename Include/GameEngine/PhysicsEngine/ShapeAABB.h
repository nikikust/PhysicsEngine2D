#pragma once
#include <GameEngine/Utils/Functions.h>


namespace physics
{
	class ShapeAABB
	{
	public:
		ShapeAABB();
		ShapeAABB(const sf::Vector2f& min, const sf::Vector2f& max);

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

		sf::Vector2f min;
		sf::Vector2f max;
	};

	ShapeAABB union_of(const ShapeAABB& AABB_A, const ShapeAABB& AABB_B);
} // namespace physics
