#include <GameEngine/PhysicsEngine/Fixture.h>
#include <GameEngine/PhysicsEngine/RigidBody.h>


namespace physics
{
	Fixture::Fixture(std::shared_ptr<Shape> shape)
		: shape_(shape)
	{
		restitution_ = 0.6f;
		friction_    = 0.6f;
		density_     = 1.0f;

		update_physical_data();
	}


	const std::shared_ptr<Shape>& Fixture::get_shape() const
	{
		return shape_;
	}

	float Fixture::get_restitution() const
	{
		return restitution_;
	}
	Fixture& Fixture::set_restitution(float restitution)
	{
		restitution_ = restitution;

		return *this;
	}


	bool Fixture::update_physical_data()
	{
		if (has_shape())
		{
			physical_data_ = shape_->calculate_physical_data(density_);

			return true;
		}

		physical_data_ = PhysicalData{};

		return false;
	}

	const PhysicalData& Fixture::get_physical_data() const
	{
		return physical_data_;
	}
	PhysicalData Fixture::get_physical_data(const sf::Vector2f axis) const
	{
		auto relative_physical_data = physical_data_;

		relative_physical_data.mmoi += relative_physical_data.mass * utils::dot(axis, axis);

		return relative_physical_data;
	}

	bool Fixture::has_shape()
	{
		return shape_ != nullptr;
	}
	
} // namespace physics
