#include <GameEngine/PhysicsEngine/RigidBody.h>


namespace physics
{
    int32_t RigidBody::max_body_id_ = 0;


    RigidBodyNodeData::RigidBodyNodeData(RigidBody* body_in)
        : body(body_in), id(body_in->get_id()) {}

    RigidBody::RigidBody()
        : node_data_(nullptr)
    {
        id_ = ++max_body_id_;

        node_data_ = new RigidBodyNodeData(this);
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
        for (auto& fixture : active_fixtures_)
        {
            auto data = fixture->get_node_data();

            data->aabb = fixture->get_AABB();

            assert(data->node_id != nullnode);

            internal_tree_.move(data->node_id, data->aabb);
        }
    }

    void RigidBody::update_internal_AABB(const sf::Vector2f offset)
    {
        internal_tree_.shift_origin(offset);
    }

    // --- Shapes
    physics::Fixture* RigidBody::add_shape(const physics::CircleShape& circle)
    {
        auto fixture = new Fixture(std::make_shared<physics::CircleShape>(circle), this);

        update_physical_data_append(fixture);

        fixtures_.push_back(fixture);
        active_fixtures_.push_back(fixture);

        auto data = fixture->get_node_data();
        data->node_id = internal_tree_.insert(data->aabb, data);

        return fixture;
    }

    physics::Fixture* RigidBody::add_shape(const physics::PolygonShape& polygon)
    {
        auto fixture = new Fixture(std::make_shared<physics::PolygonShape>(polygon), this);

        update_physical_data_append(fixture);

        fixtures_.push_back(fixture);
        active_fixtures_.push_back(fixture);

        auto data = fixture->get_node_data();
        data->node_id = internal_tree_.insert(data->aabb, data);

        return fixture;
    }

    void RigidBody::remove_fixture(uint32_t id)
    {
        for (auto it = fixtures_.begin(); it != fixtures_.end(); ++it)
        {
            if ((*it)->get_id() == id)
            {
                int32_t node_id = ((FixtureNodeData*)((*it)->get_node_data()))->node_id;

                set_active_fixture(id, false);

                fixtures_.erase(it);

                return;
            }
        }
    }

    void RigidBody::set_active_fixture(uint32_t id, bool flag)
    {
        bool is_active = false;
        std::vector<Fixture*>::iterator search_for;

        for (search_for = active_fixtures_.begin(); search_for != active_fixtures_.end(); ++search_for)
        {
            if ((*search_for)->get_id() == id)
            {
                is_active = true;

                break;
            }
        }

        if (flag == true) // need to make active
        {
            if (is_active == false)
            {
                for (const auto& fixture : fixtures_)
                {
                    if (fixture->get_id() == id)
                    {
                        auto data = fixture->get_node_data();

                        active_fixtures_.push_back(fixture);

                        data->node_id = internal_tree_.insert(data->aabb, data);

                        return;
                    }
                }
            }
            else // already added
                return; 
        }
        else // need to make inactive
        {
            if (is_active == true)
            {
                auto data = (*search_for)->get_node_data();

                internal_tree_.remove(data->node_id);

                active_fixtures_.erase(search_for);

                return;
            }
            else // already removed
                return;
        }
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

    void RigidBody::update_physical_data_append(physics::Fixture* fixture)
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

    void RigidBody::update_physical_data_remove(physics::Fixture* fixture)
    {
        // TO DO: implement.
    }

} // namespace physics
