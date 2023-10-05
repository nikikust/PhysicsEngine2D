#include <GameEngine/PhysicsEngine/RigidBody.h>


namespace physics
{
    int32_t RigidBody::max_body_id_ = 0;


    RigidBodyNodeData::RigidBodyNodeData(std::shared_ptr<RigidBody> body_in, const ShapeAABB& aabb_in, int32_t id_in)
        : body(body_in), aabb(aabb_in), id(id_in), node_id(nullnode) {}

    RigidBody::RigidBody()
        : node_data_(nullptr)
    {
        id_ = ++max_body_id_;
    }

    RigidBody::RigidBody(RigidBody&& body) noexcept
        : transform_            (std::move(body.transform_                                )),
          linear_speed_         (std::move(body.linear_speed_                             )),
          angular_speed_        (std::move(body.angular_speed_                            )),
          linear_acceleration_  (std::move(body.linear_acceleration_                      )),
          angular_acceleration_ (std::move(body.angular_acceleration_                     )),
          force_                (std::move(body.force_                                    )),
          physical_data_        (std::move(body.physical_data_                            )),
          fixed_linear_         (std::move(body.fixed_linear_                             )),
          fixed_angle_          (std::move(body.fixed_angle_                              )),
          fixtures_             (std::move(body.fixtures_                                 )),
          internal_tree_        (std::move(body.internal_tree_                            )),
          node_data_            (std::move(body.node_data_                                )),
          id_                   (std::move(body.id_                                       ))
    {}

    RigidBody::~RigidBody()
    {
        if (node_data_ != nullptr)
            free(node_data_);
    }

    // --- //
    void RigidBody::update(float delta_time, const sf::Vector2f& gravity)
    {
        linear_acceleration_ = force_ * physical_data_.inv_mass + gravity;

        linear_speed_  += linear_acceleration_  * delta_time;
        angular_speed_ += angular_acceleration_ * delta_time;

        if (fixed_linear_.first)
            linear_speed_.x = 0;
        if (fixed_linear_.second)
            linear_speed_.y = 0;
        if (fixed_angle_)
            angular_speed_ = 0;


        move   (linear_speed_  * delta_time);
        rotate (angular_speed_ * delta_time);

        force_ = { 0,0 };
    }

    void RigidBody::update_internal_AABB()
    {
        for (auto& fixture : fixtures_)
        {
            auto data = fixture->get_node_data();

            data->aabb = fixture->get_AABB();
            data->is_sleeping = fixture->is_sleeping();

            if (data->is_sleeping && data->node_id != nullnode)
            {
                internal_tree_.remove(data->node_id);
                data->node_id = nullnode;
            }
            else if (!data->is_sleeping && data->node_id == nullnode)
            {
                data->node_id = internal_tree_.insert(data->aabb, data);
            }
            else if (data->node_id != nullnode)
            {
                internal_tree_.move(data->node_id, data->aabb);
            }
        }
    }

    void RigidBody::update_internal_AABB(const sf::Vector2f offset)
    {
        internal_tree_.shift_origin(offset);
    }

    // --- Shapes
    std::shared_ptr<physics::Fixture> RigidBody::add_shape(const physics::CircleShape& circle)
    {
        auto fixture = std::make_shared<Fixture>(std::make_shared<physics::CircleShape>(circle), this);

        update_physical_data_append(fixture);

        fixtures_.push_back(fixture);

        FixtureNodeData* data = new FixtureNodeData(fixture, fixture->get_AABB(), fixture->get_shape()->get_id());
        fixture->set_node_data(data);

        data->node_id = internal_tree_.insert(fixture->get_AABB(), data);

        return fixture;
    }

    std::shared_ptr<physics::Fixture> RigidBody::add_shape(const physics::PolygonShape& polygon)
    {
        auto fixture = std::make_shared<Fixture>(std::make_shared<physics::PolygonShape>(polygon), this);

        update_physical_data_append(fixture);

        fixtures_.push_back(fixture);

        FixtureNodeData* data = new FixtureNodeData(fixture, fixture->get_AABB(), fixture->get_shape()->get_id());

        fixture->set_node_data(data);

        data->node_id = internal_tree_.insert(fixture->get_AABB(), data);

        return fixture;
    }

    void RigidBody::remove_fixture(uint32_t id)
    {
        for (auto it = fixtures_.begin(); it != fixtures_.end(); ++it)
        {
            if ((*it)->get_shape()->get_id() == id)
            {
                int32_t node_id = ((FixtureNodeData*)((*it)->get_node_data()))->node_id;

                internal_tree_.remove(node_id);

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
    void RigidBody::update_physical_data()
    {
        PhysicalData new_data{};

        // STEP 1. Find global centroid:
        for (auto& fixture : fixtures_)
        {
            if (!fixture->update_physical_data())
                continue;

            auto physical_data = fixture->get_physical_data();

            if (physical_data.mass == 0.f)
                continue;

            physical_data.centroid += fixture->get_shape()->get_position();

            if (new_data.mass == 0.f)
            {
                new_data = physical_data;

                continue;
            }

            new_data.centroid = (new_data.centroid * new_data.mass + physical_data.centroid * physical_data.mass) / 
                                (new_data.mass + physical_data.mass);

            new_data.area += physical_data.area;
            new_data.mass += physical_data.mass;
        }

        // STEP 2. Find gloabal moment of inertia:
        for (auto& fixture : fixtures_)
        {
            if (!fixture->has_shape())
                continue;

            auto physical_data = fixture->get_physical_data(new_data.centroid - fixture->get_shape()->get_position());

            if (physical_data.mass == 0.f)
                continue;

            new_data.mmoi += physical_data.mmoi;
        }

        // STEP 3. Perform final calculations:
        new_data.inv_mass = (new_data.mass > 0.f) ? 1.f / new_data.mass : 0.f;
        new_data.inv_mmoi = (new_data.mmoi > 0.f) ? 1.f / new_data.mmoi : 0.f;
        new_data.inv_mmoi = fixed_angle_ ? 0.f : new_data.inv_mmoi;

        // STEP 4. Save new data:
        physical_data_ = new_data;
        transform_.centroid = physical_data_.centroid;
    }

    void RigidBody::update_physical_data_append(std::shared_ptr<physics::Fixture> fixture)
    {
        if (!fixture->update_physical_data())
            return;

        auto physical_data_to_add = fixture->get_physical_data();

        physical_data_to_add.centroid += fixture->get_shape()->get_position();

        if (physical_data_to_add.mass == 0.f)
            return;

        if (physical_data_.mass == 0.f)
        {
            physical_data_ = physical_data_to_add;

            transform_.centroid = physical_data_.centroid;

            physical_data_.inv_mass = (physical_data_.mass > 0.f) ? 1.f / physical_data_.mass : 0.f;
            physical_data_.inv_mmoi = (physical_data_.mmoi > 0.f) ? 1.f / physical_data_.mmoi : 0.f;
            physical_data_.inv_mmoi = fixed_angle_ ? 0.f : physical_data_.inv_mmoi;

            return;
        }

        physical_data_.centroid = (physical_data_.centroid * physical_data_.mass + physical_data_to_add.centroid * physical_data_to_add.mass) /
                                  (physical_data_.mass + physical_data_to_add.mass);

        physical_data_.mass += physical_data_to_add.mass;
        physical_data_.area += physical_data_to_add.area;


        physical_data_to_add = fixture->get_physical_data(physical_data_.centroid);

        physical_data_.mmoi = physical_data_to_add.mmoi;

        for (auto& i_fixture : fixtures_)
        {
            if (!i_fixture->has_shape())
                continue;

            auto physical_data = i_fixture->get_physical_data(physical_data_.centroid - i_fixture->get_shape()->get_position());

            if (physical_data.mass == 0.f)
                continue;

            physical_data_.mmoi += physical_data.mmoi;
        }

        transform_.centroid = physical_data_.centroid;

        physical_data_.inv_mass = (physical_data_.mass > 0.f) ? 1.f / physical_data_.mass : 0.f;
        physical_data_.inv_mmoi = (physical_data_.mmoi > 0.f) ? 1.f / physical_data_.mmoi : 0.f;
        physical_data_.inv_mmoi = fixed_angle_ ? 0.f : physical_data_.inv_mmoi;
    }

    void RigidBody::update_physical_data_remove(std::shared_ptr<physics::Fixture> fixture)
    {
        // TO DO: implement.
    }

} // namespace physics
