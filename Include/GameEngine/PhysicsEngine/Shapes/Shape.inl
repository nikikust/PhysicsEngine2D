namespace physics
{
    inline Vector Shape::get_position() const
    {
        return position_;
    }

    inline void Shape::set_position(const Vector& position)
    {
        position_ = position;
    }

    inline ShapeType Shape::get_shape() const
    {
        return shape_type_;
    }

    inline int32_t Shape::get_id() const
    {
        return id_;
    }
} // namespace physics
