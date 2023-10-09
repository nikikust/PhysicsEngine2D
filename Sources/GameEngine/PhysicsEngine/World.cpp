#include <GameEngine/PhysicsEngine/World.h>


namespace physics
{
	int32_t World::max_world_id = 0;


	World::World()
	{
		id_ = ++max_world_id;
	}


	void World::update(float delta_time)
	{
#ifdef DEBUG
        debug_entities.clear();
        collision_solver_.debug_entities.clear();
#endif // DEBUG

        update_contacts();
         
        for (auto& [body_A, body_B] : contacts)
            update_body_pair(body_A, body_B);

        for (auto& [k, body] : bodies_)
        {
            body->update(delta_time, gravity_);

            tree_.move(body->get_node_data()->node_id, body->get_AABB());
        }

#ifdef DEBUGTree
        tree_.debug_entities.clear();
        tree_.draw_boxes();
        debug_entities.insert(debug_entities.begin(), tree_.debug_entities.begin(), tree_.debug_entities.end());
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
        data->node_id = tree_.insert(body->get_AABB(), data);

        return;
    }

    const std::unordered_map<int32_t, physics::RigidBody*>& World::get_bodies()
    {
        return bodies_;
    }

    void World::set_gravity(const sf::Vector2f acceleration)
    {
        gravity_ = acceleration;
    }

    void World::clear()
    {
        gravity_ = { 0.f, 0.f };

        contact_1 = nullptr;
        contacts.clear();
        tree_.reset();
        bodies_.clear();
    }

    void World::update_contacts()
    {
        contacts.clear();

        for (auto& [k, body] : bodies_)
        {
            contact_1 = body;
            tree_.query(this, body->get_AABB());
        }
    }

    void World::update_body_pair(physics::RigidBody* body_A,
                                 physics::RigidBody* body_B)
    {
        body_A->get_tree().query(this, body_B->get_tree());
    }

    void World::add_contact(void* data)
    {
        auto body = (RigidBodyNodeData*)data;

        if (contact_1->get_id() >= body->id)
            return;

        contacts.push_back({ contact_1, body->body });
    }

    void World::add_contact(void* data_1, void* data_2)
    {
        auto fixture_1 = (FixtureNodeData*)data_1;
        auto fixture_2 = (FixtureNodeData*)data_2;

        if (fixture_1->is_sleeping || fixture_2->is_sleeping)
            return;

        auto fixture_A = fixture_1->fixture;
        auto fixture_B = fixture_2->fixture;

        auto body_A = fixture_A->get_body();
        auto body_B = fixture_B->get_body();

        if (auto collision = collision_solver_.collide(fixture_A, fixture_B, body_A->get_transform(), body_B->get_transform()))
        {
            collision_solver_.separate_bodies(*collision, body_A, body_B);
            collision_solver_.write_collision_points(*collision, fixture_A, fixture_B, body_A->get_transform(), body_B->get_transform());
            collision_solver_.resolve_collision_with_rotation(*collision, body_A, body_B);
        }
    }

#ifdef DEBUG
    const std::vector<graphics::DebugDraw>& World::get_debug_entities()
    {
        debug_entities.insert(debug_entities.end(), collision_solver_.debug_entities.begin(), collision_solver_.debug_entities.end());
        return debug_entities;
    }
#endif // DEBUG


} // namespace physics
