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
        for (auto& body_pair_A : bodies_)
        {
            auto& body_A = body_pair_A.second;

            for (auto& body_pair_B : bodies_)
            {
                auto& body_B = body_pair_B.second;

                if (body_A->get_id() >= body_B->get_id())
                    continue;

                update_body_pair(body_A, body_B);
            }

            body_A->update(delta_time, gravity_);

            body_A->wrap_to_screen(sf::Vector2u{2560, 1040}); // to keep object inside screen
        }
	}

    std::shared_ptr<physics::RigidBody> World::get_body(int32_t id)
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

    void World::update_body_pair(const std::shared_ptr<physics::RigidBody>& body_A,
                                 const std::shared_ptr<physics::RigidBody>& body_B)
    {
        for (auto& shape_pair_A : body_A->get_fixtures())
        {
            auto& fixture_A = shape_pair_A.second;
            auto& shape_A   = fixture_A->get_shape();

            for (auto& shape_pair_B : body_B->get_fixtures())
            {
                auto& fixture_B = shape_pair_B.second;
                auto& shape_B = fixture_B->get_shape();

                std::optional<CollisionInfo> collision = std::nullopt;

                switch (shape_A->get_shape()) {
                case ShapeType::Rectangle:
                    switch (shape_B->get_shape()) {
                    case ShapeType::Rectangle: collision = collision_solver_.polygons_collision       (fixture_A, fixture_B, body_A->get_transform(), body_B->get_transform()); break;
                    case ShapeType::Circle:    collision = collision_solver_.polygon_circle_collision (fixture_A, fixture_B, body_A->get_transform(), body_B->get_transform()); break;
                    default: break;
                    } break;
                case ShapeType::Circle:
                    switch (shape_B->get_shape()) {
                    case ShapeType::Rectangle: collision = collision_solver_.circle_polygon_collision (fixture_A, fixture_B, body_A->get_transform(), body_B->get_transform()); break;
                    case ShapeType::Circle:    collision = collision_solver_.circles_collision        (fixture_A, fixture_B, body_A->get_transform(), body_B->get_transform()); break;
                    default: break;
                    } break;
                default: break;
                }

                if (collision)
                {
                    collision_solver_.resolve_collision(*collision, body_A, body_B);
                }
            }
        }
    }

} // namespace physics
