#pragma once
#include <GameEngine/Utils/Functions.h>


namespace physics
{
	class ShapeAABB
	{
	public:
		ShapeAABB();


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

		sf::Vector2f min;
		sf::Vector2f max;
	};
} // namespace physics
