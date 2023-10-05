#include <GameEngine/PhysicsEngine/PhysMath.h>


namespace physics
{
	bool operator==(const Transform& left, const Transform& right)
	{
		return
			physics::almost_equal(left.rotation.get_angle(), right.rotation.get_angle()) &&
			physics::almost_equal(left.position,             right.position            ) &&
			physics::almost_equal(left.centroid,             right.centroid            );
	}

	bool operator!=(const Transform& left, const Transform& right)
	{
		return
			!physics::almost_equal(left.rotation.get_angle(), right.rotation.get_angle()) ||
			!physics::almost_equal(left.position,             right.position            ) ||
			!physics::almost_equal(left.centroid,             right.centroid            );
	}

	Transform::Transform() {}

	Transform::Transform(Transform& transform)
		: position(transform.position), centroid(transform.centroid), rotation(transform.rotation)
	{
	}

	Transform::Transform(Transform&& transform) noexcept
		: position(std::move(transform.position)), centroid(std::move(transform.centroid)), rotation(std::move(transform.rotation))
	{
	}

	Transform& Transform::operator=(const Transform& b)
	{
		this->position = b.position;
		this->centroid = b.centroid;
		this->rotation = b.rotation;

		return *this;
	}
} // namespace physics
