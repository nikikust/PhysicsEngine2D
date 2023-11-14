namespace physics
{
    // Inline section
    inline RigidBody& RigidBody::set_position(const Vector& position)
    {
        auto delta = position - transform_.position;

        transform_.position = position;

        update_internal_AABB(delta);

        return *this;
    }

    inline RigidBody& RigidBody::set_angle(float angle)
    {
        transform_.rotation.set_angle(angle);

        update_internal_AABB();

        return *this;
    }

    inline RigidBody& RigidBody::set_linear_speed(const Vector& linear_speed)
    {
        linear_speed_ = linear_speed;

        return *this;
    }

    inline RigidBody& RigidBody::set_angular_speed(float angular_speed)
    {
        angular_speed_ = angular_speed;

        return *this;
    }

    inline RigidBody& RigidBody::set_linear_acceleration(const Vector& linear_acceleration)
    {
        linear_acceleration_ = linear_acceleration;

        return *this;
    }

    inline RigidBody& RigidBody::set_angular_acceleration(float angular_acceleration)
    {
        angular_acceleration_ = angular_acceleration;

        return *this;
    }

    inline RigidBody& RigidBody::set_force(const Vector& force)
    {
        force_ = force;

        return *this;
    }

    inline RigidBody& RigidBody::set_linear_fixation(bool x, bool y)
    {
        fixed_linear_ = { x, y };

        return *this;
    }

    inline RigidBody& RigidBody::set_angular_fixation(bool a)
    {
        fixed_angle_ = a;

        return *this;
    }

    inline const Vector& RigidBody::get_position() const
    {
        return transform_.position;
    }

    inline float RigidBody::get_angle() const
    {
        return transform_.rotation.get_angle();
    }

    inline const Transform& RigidBody::get_transform() const
    {
        return transform_;
    }

    inline const Vector& RigidBody::get_linear_speed() const
    {
        return linear_speed_;
    }

    inline float RigidBody::get_angular_speed() const
    {
        return angular_speed_;
    }

    inline const Vector& RigidBody::get_linear_acceleration() const
    {
        return linear_acceleration_;
    }

    inline float RigidBody::get_angular_acceleration() const
    {
        return angular_acceleration_;
    }

    inline const Vector& RigidBody::get_force() const
    {
        return force_;
    }

    inline float RigidBody::get_inv_mass() const
    {
        return physical_data_.inv_mass;
    }

    inline float RigidBody::get_inv_mmoi() const
    {
        return physical_data_.inv_mmoi;
    }

    inline std::pair<bool, bool> RigidBody::get_linear_fixation()
    {
        return fixed_linear_;
    }

    inline bool RigidBody::get_angular_fixation()
    {
        return fixed_angle_;
    }

    inline RigidBody& RigidBody::move(const Vector& delta)
    {
        transform_.position += delta;

        //update_internal_AABB(delta);

        return *this;
    }

    inline RigidBody& RigidBody::accelerate(const Vector& delta)
    {
        linear_speed_ += delta;

        return *this;
    }

    inline RigidBody& RigidBody::rotate(float angle)
    {
        transform_.rotation.rotate(angle);

        update_internal_AABB();

        return *this;
    }

    inline RigidBody& RigidBody::spin(float angle)
    {
        angular_speed_ += angle;

        return *this;
    }

    inline ShapeAABB RigidBody::get_AABB() const
    {
        return internal_tree_.get_root_AABB();
    }

    inline RigidBodyNodeData* RigidBody::get_node_data() const
    {
        return node_data_;
    }

    inline void RigidBody::set_node_data(RigidBodyNodeData* data)
    {
        node_data_ = data;
    }

    inline physics::Fixture* RigidBody::get_fixture(uint32_t id) const
    {
        for (auto& fixture : fixtures_)
            if (fixture->get_id() == id)
                return fixture;

        return nullptr;
    }

    inline const std::vector<physics::Fixture*>& RigidBody::get_fixtures() const
    {
        return fixtures_;
    }

    inline const DAABBTree& RigidBody::get_tree() const
    {
        return internal_tree_;
    }

    inline DAABBTree& RigidBody::get_tree()
    {
        return internal_tree_;
    }

    inline int32_t RigidBody::get_id() const
    {
        return id_;
    }


#ifdef DAMPING
    inline void RigidBody::dump_speed(float delta_time)
    {
        // TODO: delta_time use
        linear_speed_.x *= fmaxf(0.2f * powf(linear_speed_.x / 110.f, 1.5f), 0.2f);
        linear_speed_.y *= fmaxf(0.2f * powf(linear_speed_.y / 110.f, 1.5f), 0.2f);
    }
#endif // DAMPING
} // namespace physics
