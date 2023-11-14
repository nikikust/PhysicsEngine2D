namespace physics
{
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
