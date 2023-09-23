#include <GameEngine/PhysicsEngine/RigidBody.h>


namespace physics
{
	int32_t RigidBody::max_body_id_ = 0;


	RigidBody::RigidBody()
	{
		id_ = ++max_body_id_;
	}

	// --- //

    RigidBody& RigidBody::set_transform(const physics::Transform& transform)
    {
        transform_ = transform;

        return *this;
    }
    RigidBody& RigidBody::set_mass(float mass)
    {
        mass_ = mass;

        return *this;
    }
    RigidBody& RigidBody::set_linear_speed(const sf::Vector2f& linear_speed)
    {
        linear_speed_ = linear_speed;

        return *this;
    }
    RigidBody& RigidBody::set_angular_speed(float angular_speed)
    {
        angular_speed_ = angular_speed;

        return *this;
    }
    RigidBody& RigidBody::set_linear_acceleration(const sf::Vector2f& linear_acceleration)
    {
        linear_acceleration_ = linear_acceleration;

        return *this;
    }
    RigidBody& RigidBody::set_angular_acceleration(float angular_acceleration)
    {
        angular_acceleration_ = angular_acceleration;

        return *this;
    }
    RigidBody& RigidBody::set_force(const sf::Vector2f& force)
    {
        force_ = force;

        return *this;
    }

    RigidBody& RigidBody::set_linear_fixation(bool x, bool y)
    {
        fixed_linear_ = { x, y };

        return *this;
    }
    RigidBody& RigidBody::set_angular_fixation(bool a)
    {
        fixed_angle_ = a;

        return *this;
    }

    const Transform& RigidBody::get_transform() const
    {
        return transform_;
    }
    float RigidBody::get_mass() const
    {
        return mass_;
    }
    const sf::Vector2f& RigidBody::get_linear_speed() const
    {
        return linear_speed_;
    }
    float RigidBody::get_angular_speed() const
    {
        return angular_speed_;
    }
    const sf::Vector2f& RigidBody::get_linear_acceleration() const
    {
        return linear_acceleration_;
    }
    float RigidBody::get_angular_acceleration() const
    {
        return angular_acceleration_;
    }
    const sf::Vector2f& RigidBody::get_force() const
    {
        return force_;
    }

    std::pair<bool, bool> RigidBody::get_linear_fixation()
    {
        return fixed_linear_;
    }
    bool RigidBody::get_angular_fixation()
    {
        return fixed_angle_;
    }

    sf::Vector2f RigidBody::get_center_of_mass() const
    {
        return transform_.position;
    }
    float RigidBody::get_moment_of_inertia() const
    {
        return moment_of_inertia_;
    }

    RigidBody& RigidBody::move(const sf::Vector2f& delta)
    {
        transform_.position += delta;

        return *this;
    }
    RigidBody& RigidBody::accelerate(const sf::Vector2f& delta)
    {
        linear_speed_ += delta;

        return *this;
    }
    RigidBody& RigidBody::rotate(float angle)
    {
        transform_.angle += angle;

        return *this;
    }
    RigidBody& RigidBody::spin(float angle)
    {
        angular_speed_ += angle;

        return *this;
    }

    // --- //
    void RigidBody::update(float delta_time, const sf::Vector2f& gravity)
    {
        linear_acceleration_ = force_ / mass_ + gravity;

        linear_speed_ += linear_acceleration_ * delta_time;
        angular_speed_ += angular_acceleration_ * delta_time;

        if (fixed_linear_.first)
            linear_speed_.x = 0;
        if (fixed_linear_.second)
            linear_speed_.y = 0;
        if (fixed_angle_)
            angular_speed_ = 0;

        transform_.position += linear_speed_ * delta_time;
        transform_.angle += angular_speed_ * delta_time;

        force_ = { 0,0 };
    }
    void RigidBody::wrap_to_screen(const sf::Vector2u& window_size)
    {
        sf::Vector2f pos{
            transform_.position.x / (float)window_size.x,
            transform_.position.y / (float)window_size.y
        };

        if (pos.x < 0)
            pos.x = 1.f - fmodf(fabsf(pos.x), 1.f);
        else if (pos.x > 1)
            pos.x = fmodf(pos.x, 1.f);

        if (pos.y < 0)
            pos.y = 1.f - fmodf(fabsf(pos.y), 1.f);
        else if (pos.y > 1)
            pos.y = fmodf(pos.y, 1.f);

        pos.x *= (float)window_size.x;
        pos.y *= (float)window_size.y;

        transform_.position = pos;
    }

    // --- Shapes
    std::shared_ptr<physics::Fixture> RigidBody::add_shape(const physics::CircleShape& circle)
    {
        Fixture fixture{ std::make_shared<physics::CircleShape>(circle), this };

        fixtures_.push_back(std::make_shared<physics::Fixture>(fixture));

        return fixtures_.back();
    }
    std::shared_ptr<physics::Fixture> RigidBody::add_shape(const physics::PolygonShape& polygon)
    {
        Fixture fixture{ std::make_shared<physics::PolygonShape>(polygon), this };

        fixtures_.push_back(std::make_shared<physics::Fixture>(fixture));

        return fixtures_.back();
    }

    std::shared_ptr<physics::Fixture> RigidBody::get_fixture(uint32_t id) const
    {
        for (auto& fixture : fixtures_)
            if (fixture->get_shape()->get_id() == id)
                return fixture;

        return nullptr;
    }
    void RigidBody::remove_fixture(uint32_t id)
    {
        for (auto it = fixtures_.begin(); it != fixtures_.end(); ++it)
        {
            if ((*it)->get_shape()->get_id() == id)
            {
                fixtures_.erase(it);

                return;
            }
        }
    }

    const std::vector<std::shared_ptr<physics::Fixture>>& RigidBody::get_fixtures() const
    {
        return fixtures_;
    }

    // --- //
    int32_t RigidBody::get_id() const
    {
        return id_;
    }

} // namespace physics
