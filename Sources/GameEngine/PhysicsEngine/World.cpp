#include <GameEngine/PhysicsEngine/World.h>


#ifdef USE_GRAVITY
sf::Vector2f physics::World::gravity_{ 0.f, 980.f };
#else
sf::Vector2f physics::World::gravity_{ 0.f, 0.f };
#endif

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
        collision_solver_.debug_entities.clear();
        tree_.debug_entities.clear();
#endif // DEBUG

        update_contacts();

        for (auto& [body_A, body_B] : contacts)
            update_body_pair(body_A, body_B);

        for (auto& [k, body] : bodies_)
        {
            body->update(delta_time, gravity_);

            tree_.move(body->get_node_data()->node_id, body->get_AABB());
        }
#ifdef DEBUG
        debug_entities.clear();

        tree_.draw_boxes();
        debug_entities = tree_.debug_entities;

        // for (auto& [k, body] : bodies_)
        // {
        //     auto corner{ body->get_AABB().max - body->get_AABB().min };
        // 
        //     debug_entities.push_back(graphics::DebugDraw{ graphics::DebugDraw::Border, body->get_AABB().min, sf::Color::Green, 0, 0,
        //         { { 0.f, 0.f }, { corner.x, 0.f }, { corner.x, corner.y }, { 0.f, corner.y } } });
        // }
#endif // DEBUG
	}

    std::shared_ptr<physics::RigidBody> World::get_body(int32_t id) const
    {
        if (bodies_.contains(id))
            return bodies_.at(id);

        return nullptr;
    }

    void World::add_body(std::shared_ptr<physics::RigidBody> body)
    {
        bodies_.insert({ body->get_id(), body});

        RigidBodyNodeData* data = new RigidBodyNodeData(body, body->get_AABB(), body->get_id());
        body->set_node_data(data);

        data->node_id = tree_.insert(body->get_AABB(), data);

        return;
    }

    const std::unordered_map<int32_t, std::shared_ptr<physics::RigidBody>>& World::get_bodies()
    {
        return bodies_;
    }


    void World::update_body_pair(const std::shared_ptr<physics::RigidBody>& body_A,
                                 const std::shared_ptr<physics::RigidBody>& body_B)
    {
        for (auto& fixture_A : body_A->get_fixtures())
        {
            if (fixture_A->is_sleeping())
                continue;

            for (auto& fixture_B : body_B->get_fixtures())
            {
                if (fixture_B->is_sleeping())
                    continue;

                if (auto collision = collision_solver_.collide(fixture_A, fixture_B, body_A->get_transform(), body_B->get_transform()))
                {
                    collision_solver_.separate_bodies                 (*collision, body_A, body_B);
                    collision_solver_.write_collision_points          (*collision, fixture_A, fixture_B, body_A->get_transform(), body_B->get_transform());
                    collision_solver_.resolve_collision_with_rotation (*collision, body_A, body_B);
                }
            }
        }
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

    void World::add_contact(void* data)
    {
        auto body = (RigidBodyNodeData*)data;

        if (contact_1->get_id() >= body->id)
            return;

        contacts.push_back({ contact_1, body->body.lock() });
    }

#ifdef DEBUG
    const std::vector<graphics::DebugDraw>& World::get_debug_entities()
    {
        debug_entities.insert(debug_entities.end(), collision_solver_.debug_entities.begin(), collision_solver_.debug_entities.end());
        return debug_entities;
    }
#endif // DEBUG


} // namespace physics
