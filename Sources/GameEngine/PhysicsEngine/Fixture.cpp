#include <GameEngine/PhysicsEngine/Fixture.h>
#include <GameEngine/PhysicsEngine/RigidBody.h>


namespace physics
{
    FixtureNodeData::FixtureNodeData(std::shared_ptr<Fixture> fixture_in, const ShapeAABB& aabb_in, int32_t id_in)
        : fixture(fixture_in), aabb(aabb_in), is_sleeping(false), id(id_in), node_id(nullnode) {}

    Fixture::Fixture(std::shared_ptr<Shape> shape, RigidBody* body)
        : shape_(shape), body_(body), node_data_(nullptr)
    {
        restitution_ = 0.6f;
        friction_    = 0.6f;
        density_     = 1.0f;

        sleeping_ = false;

        // --- Calculate base AABB
        base_AABB_.reset();

        switch (shape_->get_shape())
        {
        case ShapeType::Circle:
        {
            auto circle = std::dynamic_pointer_cast<CircleShape>(shape_);

            auto radius = circle->get_radius();

            base_AABB_.min = { -sf::Vector2f{radius, radius} };
            base_AABB_.max = {  sf::Vector2f{radius, radius} };
        }
        break;
        case ShapeType::Polygon:
        {
            auto polygon = std::dynamic_pointer_cast<PolygonShape>(shape_);

            auto max_distance_squared = 0.f;

            for (auto& vertex : polygon->get_vertices())
            {
                max_distance_squared = fmaxf(max_distance_squared, utils::length_squared(vertex));
            }

            auto max_distance = sqrtf(max_distance_squared);

            base_AABB_.min = { -sf::Vector2f{max_distance, max_distance} };
            base_AABB_.max = {  sf::Vector2f{max_distance, max_distance} };
        }
        break;
        default:
            throw("Unknown shape type to calculate AABB!");
        }

        cached_AABB_ = base_AABB_;

        auto position_rotated = physics::rotate_and_move_point(shape_->get_position(), body->get_transform());
        cached_AABB_.move(position_rotated);

        update_physical_data();
    }

    Fixture::~Fixture()
    {
        if (node_data_ != nullptr)
            free(node_data_);

        shape_ = nullptr;
        body_ = nullptr;
    }


    const ShapeAABB& Fixture::get_AABB()
    {
        cached_AABB_ = base_AABB_;

        ShapeAABB new_AABB{ base_AABB_ };

        auto position_rotated = physics::rotate_and_move_point(shape_->get_position(), body_->get_transform());
        cached_AABB_.move(position_rotated);

        return cached_AABB_;
    }

    bool Fixture::update_physical_data()
    {
        if (has_shape())
        {
            physical_data_ = shape_->calculate_physical_data(density_);

            return true;
        }

        physical_data_ = PhysicalData{};

        return false;
    }

    Fixture& Fixture::set_sleeping(bool flag)
    {
        sleeping_ = flag;

        assert(node_data_ != nullptr);

        if (flag == true)
            node_data_->aabb = get_AABB();
        node_data_->is_sleeping = flag;

        assert(body_ != nullptr);

        body_->set_active_fixture(shape_->get_id(), !flag);

        return *this;
    }
} // namespace physics
