#include <GameEngine/PhysicsEngine/World.h>


namespace physics
{
    int32_t World::max_world_id = 0;


    World::World()
    {
        id_ = ++max_world_id;

        contact_1_ = nullptr;

        ShapeAABB aabb{ {5.f, 5.f}, {10.f, 10.f} };
        Ray ray{ {0.f, 0.f}, utils::normalize({1.f, 1.f}) };
        sf::Vector2f result{};

        std::cout << "Result 1: " << intersect(ray, aabb, result) << " | X: " << result.x << " Y: " << result.y << std::endl << std::endl;

        RayHitInfo hit_info;
        bool inter = aabb.cast_ray(ray, hit_info);

        result = ray.origin + ray.direction * hit_info.fraction;

        std::cout << "Result 2: " << inter << " | X: " << result.x << " Y: " << result.y << std::endl << std::endl;
    }


    void World::update(float delta_time)
    {
#ifdef DEBUG
        debug_entities.clear();
        collision_solver_.debug_entities.clear();
#endif // DEBUG

        update_bodies_contacts();
        
        update_fixtures_contacts();

        collide_fixtures();

        solve_contacts();

        update_bodies(delta_time);

#ifdef DEBUGTree
        world_tree_.debug_entities.clear();
        world_tree_.draw_boxes();
        debug_entities.insert(debug_entities.begin(), world_tree_.debug_entities.begin(), world_tree_.debug_entities.end());
#endif // DEBUGTree

#ifdef DEBUGBodyTree
        for (auto& [k, body] : bodies_)
        {
            auto& tree = body->get_tree();

            tree.debug_entities.clear();
            tree.draw_boxes();

            debug_entities.insert(debug_entities.begin(), tree.debug_entities.begin(), tree.debug_entities.end());
        }
#endif // DEBUGBodyTree

    }

    physics::RigidBody* World::get_body(int32_t id) const
    {
        if (bodies_.contains(id))
            return bodies_.at(id);

        return nullptr;
    }

    void World::add_body(physics::RigidBody* body)
    {
        bodies_.insert({ body->get_id(), body});

        auto data = body->get_node_data();
        data->node_id = world_tree_.insert(body->get_AABB(), data);

        return;
    }

    const std::unordered_map<int32_t, physics::RigidBody*>& World::get_bodies() const
    {
        return bodies_;
    }

    void World::set_gravity(const sf::Vector2f& acceleration)
    {
        gravity_ = acceleration;
    }

    void World::cast_ray(RayCastCallback* callback, const physics::Ray& ray)
    {
        WorldRayCastWrapper wrapper{ callback, ray };

        world_tree_.cast_ray(&wrapper, ray);
    }

    void World::clear()
    {
        gravity_ = { 0.f, 0.f };

        contact_1_ = nullptr;
        body_contacts_.clear();
        world_tree_.reset();
        bodies_.clear();
    }

    void World::update_bodies_contacts()
    {
        body_contacts_.clear();

        for (auto& [k, body] : bodies_)
        {
            contact_1_ = body;
            world_tree_.query(this, body->get_AABB());
        }
    }

    void World::update_fixtures_contacts()
    {
        fixture_contacts_.clear();

        for (auto& [body_A, body_B] : body_contacts_)
        {
            body_A->get_tree().query(this, body_B->get_tree());
        }
    }

    void World::collide_fixtures()
    {
        // auto isnt_colliding = [this](physics::CollisionInfo& collision) {
        //     return this->collision_solver_.collide(collision) == false; 
        // };
        // 
        // auto it{ std::remove_if(fixture_contacts_.begin(), fixture_contacts_.end(), isnt_colliding) };
        // 
        // fixture_contacts_.erase(it, fixture_contacts_.end());
    }

    void World::solve_contacts()
    {
        for (auto& collision : fixture_contacts_)
        {
            if (this->collision_solver_.collide(collision) == false)
                continue;

            auto fixture_A = collision.fixture_A;
            auto fixture_B = collision.fixture_B;

            auto body_A = fixture_A->get_body();
            auto body_B = fixture_B->get_body();

            collision_solver_.separate_bodies                 (collision, body_A, body_B);
            collision_solver_.write_collision_points          (collision, fixture_A, fixture_B, body_A->get_transform(), body_B->get_transform());
            collision_solver_.resolve_collision_with_rotation (collision, body_A, body_B);
        }
    }

    void World::update_bodies(float delta_time)
    {
        for (auto& [k, body] : bodies_)
        {
            body->update(delta_time, gravity_);

            world_tree_.move(body->get_node_data()->node_id, body->get_AABB());
        }
    }

    void World::add_contact_bodies(void* data)
    {
        auto body = (RigidBodyNodeData*)data;

        if (contact_1_->get_id() >= body->id)
            return;

        body_contacts_.push_back({ contact_1_, body->body });
    }

    void World::add_contact_fixtures(void* data_1, void* data_2)
    {
        auto fixture_node_data_1 = (FixtureNodeData*)data_1;
        auto fixture_node_data_2 = (FixtureNodeData*)data_2;

        if (fixture_node_data_1->is_sleeping || fixture_node_data_2->is_sleeping)
            return;

        auto fixture_A = fixture_node_data_1->fixture;
        auto fixture_B = fixture_node_data_2->fixture;

        if (fixture_A->get_id() >= fixture_B->get_id())
            return;

        fixture_contacts_.push_back(CollisionInfo{ fixture_A, fixture_B });
    }

#ifdef DEBUG
    const std::vector<graphics::DebugDraw>& World::get_debug_entities()
    {
        debug_entities.insert(debug_entities.end(), collision_solver_.debug_entities.begin(), collision_solver_.debug_entities.end());
        return debug_entities;
    }
#endif // DEBUG


} // namespace physics
