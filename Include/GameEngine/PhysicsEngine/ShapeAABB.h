#pragma once
#include <GameEngine/Utils/Functions.h>


namespace physics
{
	class ShapeAABB
	{
	public:
		ShapeAABB();


		/// Returns true if two AABBs collided
		bool collides(const ShapeAABB& aabb);

		/// Recalculates min and max points with new point
		void add_point(const sf::Vector2f& point);

		/// @brief Combines two AABBs to cover both 
		void combine(const ShapeAABB& aabb);

		sf::Vector2f min;
		sf::Vector2f max;
	};
} // namespace physics
