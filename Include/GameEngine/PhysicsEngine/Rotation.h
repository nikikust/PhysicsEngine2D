#pragma once
#include <cstdlib>
#include <memory>


namespace physics
{
	class Rotation
	{
	public:
		Rotation();
		Rotation(float angle);
		Rotation(Rotation&);
		Rotation(Rotation&&) noexcept;
		Rotation& operator=(const Rotation& b);


		void set_angle(float angle);
		void rotate(float angle);

		float get_angle() const;
		float get_sin() const;
		float get_cos() const;

	private:
		float angle_;
		float sin_;
		float cos_;
	};


	// Inline section
	inline void Rotation::set_angle(float angle)
	{
		angle_ = angle;
		sin_ = sinf(angle_);
		cos_ = cosf(angle_);
	}
	
	inline void Rotation::rotate(float angle)
	{
		angle_ += angle;
		sin_ = sinf(angle_);
		cos_ = cosf(angle_);
	}
	
	inline float Rotation::get_angle() const
	{
		return angle_;
	}
	
	inline float Rotation::get_sin() const
	{
		return sin_;
	}
	
	inline float Rotation::get_cos() const
	{
		return cos_;
	}
} // namespace physics
