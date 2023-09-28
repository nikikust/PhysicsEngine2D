#include <GameEngine/PhysicsEngine/ShapeAABB.h>


namespace physics
{
	ShapeAABB::ShapeAABB()
		: min({ std::numeric_limits<float>::max   (), std::numeric_limits<float>::max   () }),
	 	  max({ std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest() }) {}


	bool ShapeAABB::collides(const ShapeAABB& aabb)
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
		min.x = fminf(min.x, point.x);
		min.y = fminf(min.y, point.y);
		max.x = fmaxf(max.x, point.x);
		max.y = fmaxf(max.y, point.y);
	}
	
	void ShapeAABB::combine(const ShapeAABB& aabb)
	{
		add_point(aabb.min);
		add_point(aabb.max);
	}
} // namespace physics
