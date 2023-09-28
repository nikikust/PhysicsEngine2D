#include <GameEngine/PhysicsEngine/World.h>


#define USE_GRAVITY

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
#endif // DEBUG

        for (auto& [k_A, body_A] : bodies_)
        {
            for (auto& [k_B, body_B] : bodies_)
            {
                if (body_A->get_id() >= body_B->get_id())
                    continue;

                if (!broad_check(body_A, body_B))
                    continue;

                update_body_pair(body_A, body_B);
            }
        }

        for (auto& [k, body] : bodies_)
            body->update(delta_time, gravity_);
	}

    std::shared_ptr<physics::RigidBody> World::get_body(int32_t id) const
    {
        if (bodies_.contains(id))
            return bodies_.at(id);

        return nullptr;
    }

    std::shared_ptr<physics::RigidBody> World::add_body(const physics::RigidBody& body)
    {
        bodies_.insert({ body.get_id(), std::make_shared<physics::RigidBody>(body) });

        return bodies_.at(body.get_id());
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
            for (auto& fixture_B : body_B->get_fixtures())
            {
                if (auto collision = collision_solver_.collide(fixture_A, fixture_B, body_A->get_transform(), body_B->get_transform()))
                {
                    collision_solver_.separate_bodies         (*collision, body_A, body_B);
                    collision_solver_.write_collision_points  (*collision, fixture_A, fixture_B, body_A->get_transform(), body_B->get_transform());
                    collision_solver_.resolve_collision_basic (*collision, body_A, body_B);
                }
            }
        }
    }

    bool World::broad_check(const std::shared_ptr<physics::RigidBody>& body_A, const std::shared_ptr<physics::RigidBody>& body_B)
    {
        return body_A->get_AABB().collides(body_B->get_AABB());
    }

#ifdef DEBUG
    const std::vector<graphics::DebugDraw>& World::get_debug_entities()
    {
        return collision_solver_.debug_entities;
    }
#endif // DEBUG


} // namespace physics
