namespace physics
{
    inline Shape* Fixture::get_shape() const
    {
        return shape_;
    }

    inline FixtureNodeData* Fixture::get_node_data() const
    {
        return node_data_;
    }

    inline Fixture& Fixture::set_node_data(FixtureNodeData* data)
    {
        node_data_ = data;

        return *this;
    }

    inline float Fixture::get_restitution() const
    {
        return restitution_;
    }

    inline Fixture& Fixture::set_restitution(float restitution)
    {
        restitution_ = restitution;

        return *this;
    }

    inline const PhysicalData& Fixture::get_physical_data() const
    {
        return physical_data_;
    }

    inline PhysicalData Fixture::get_physical_data(const Vector axis) const
    {
        auto relative_physical_data = physical_data_;

        relative_physical_data.mmoi += relative_physical_data.mass * dot(axis, axis);

        return relative_physical_data;
    }

    inline RigidBody* Fixture::get_body() const
    {
        return body_;
    }

    inline int32_t Fixture::get_id() const
    {
        return shape_->get_id();
    }

    inline bool Fixture::has_shape()
    {
        return shape_ != nullptr;
    }

    inline bool Fixture::is_sleeping()
    {
        return node_data_->is_sleeping;
    }
} // namespace physics
