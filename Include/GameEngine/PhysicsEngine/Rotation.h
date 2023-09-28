#pragma once
#include <cstdlib>


namespace physics
{
	class Rotation
	{
	public:
		Rotation();
		Rotation(float angle);


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
} // namespace physics
