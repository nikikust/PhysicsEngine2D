#include <GameEngine/PhysicsEngine/CollisionSolver.h>


namespace physics
{
#ifdef DEBUG
    std::vector<graphics::DebugDraw> CollisionSolver::debug_entities{};
#endif // DEBUG

    CollisionSolver::CollisionSolver()
    {
    }

    // --- Collision detection

    std::optional<CollisionInfo> CollisionSolver::collide(std::shared_ptr<Fixture> fixture_A, std::shared_ptr<Fixture> fixture_B, const Transform& transform_A, const Transform& transform_B)
    {
        auto& shape_A = fixture_A->get_shape();
        auto& shape_B = fixture_B->get_shape();

        switch (shape_A->get_shape()) {
        case ShapeType::Rectangle:
            switch (shape_B->get_shape()) {
            case ShapeType::Rectangle: return polygons_collision       (fixture_A, fixture_B, transform_A, transform_B); break;
            case ShapeType::Circle:    return polygon_circle_collision (fixture_A, fixture_B, transform_A, transform_B); break;
            default: break;
            } break;
        case ShapeType::Circle:
            switch (shape_B->get_shape()) {
            case ShapeType::Rectangle: return circle_polygon_collision (fixture_A, fixture_B, transform_A, transform_B); break;
            case ShapeType::Circle:    return circles_collision        (fixture_A, fixture_B, transform_A, transform_B); break;
            default: break;
            } break;
        default: break;
        }

        return std::nullopt;
    }

    std::optional<CollisionInfo> CollisionSolver::circles_collision(std::shared_ptr<Fixture> circle_A_raw, std::shared_ptr<Fixture> circle_B_raw, 
                                                                    const Transform& transform_A, const Transform& transform_B) const
    {
        // Convert pointers
        auto circle_A = std::dynamic_pointer_cast<CircleShape>(circle_A_raw->get_shape());
        auto circle_B = std::dynamic_pointer_cast<CircleShape>(circle_B_raw->get_shape());

        // Prepare data
        auto position_A = physics::rotate_and_move_point(circle_A->get_position(), transform_A);
        auto position_B = physics::rotate_and_move_point(circle_B->get_position(), transform_B);

        auto radius_A = circle_A->get_radius();
        auto radius_B = circle_B->get_radius();

        auto distance = utils::distance(position_A, position_B);

        if (distance < radius_A + radius_B)
        {
            return { { 
                {},
                utils::normalize(position_B - position_A),
                radius_A + radius_B - distance,
                fminf(circle_A_raw->get_restitution(), circle_B_raw->get_restitution()),
            } };
        }
        else
            return std::nullopt;
    }

    std::optional<CollisionInfo> CollisionSolver::polygons_collision(std::shared_ptr<Fixture> polygon_A_raw, std::shared_ptr<Fixture> polygon_B_raw, 
                                                                     const Transform& transform_A, const Transform& transform_B) const
    {
        // Convert pointers
        auto polygon_A = std::dynamic_pointer_cast<PolygonShape>(polygon_A_raw->get_shape());
        auto polygon_B = std::dynamic_pointer_cast<PolygonShape>(polygon_B_raw->get_shape());

        // --- //

        auto& vertices_A = polygon_A->get_vertices();
        auto& vertices_B = polygon_B->get_vertices();

        auto polygon_A_position = polygon_A->get_position();
        auto polygon_B_position = polygon_B->get_position();

        auto polygon_A_position_rotated = physics::rotate_and_move_point(polygon_A_position, transform_A);
        auto polygon_B_position_rotated = physics::rotate_and_move_point(polygon_B_position, transform_B);

        float total_min_depth = std::numeric_limits<float>::max();
        sf::Vector2f normal{};

        auto count = (int32_t)vertices_A.size();
        for (int32_t i = 0; i < count; ++i)
        {
            int32_t i_and_one = (i == count - 1) ? 0 : i + 1;
            auto point_A = physics::rotate_and_move_point(polygon_A_position + vertices_A.at(i), transform_A);
            auto point_B = physics::rotate_and_move_point(polygon_A_position + vertices_A.at(i_and_one), transform_A);

            auto edge = point_B - point_A;
            auto axis = utils::normalize(sf::Vector2f(-edge.y, edge.x));

            auto [projections_A_min, projections_A_max] = polygon_projection(polygon_A, axis, transform_A);
            auto [projections_B_min, projections_B_max] = polygon_projection(polygon_B, axis, transform_B);

            if (projections_A_max < projections_B_min || projections_B_max < projections_A_min)
                return std::nullopt;

            float min_depth = std::min(projections_A_max - projections_B_min, projections_B_max - projections_A_min);

            if (min_depth < total_min_depth)
            {
                total_min_depth = min_depth;

                if (utils::dot(polygon_B_position_rotated - polygon_A_position_rotated, axis) < 0.f)
                    normal = -axis;
                else
                    normal = axis;
            }
        }

        count = (int32_t)vertices_B.size();
        for (int32_t i = 0; i < count; ++i)
        {
            int32_t i_and_one = (i == count - 1) ? 0 : i + 1;
            auto point_A = physics::rotate_and_move_point(polygon_B_position + vertices_B.at(i), transform_B);
            auto point_B = physics::rotate_and_move_point(polygon_B_position + vertices_B.at(i_and_one), transform_B);

            auto edge = point_B - point_A;
            auto axis = utils::normalize(sf::Vector2f(-edge.y, edge.x));

            auto [projections_A_min, projections_A_max] = polygon_projection(polygon_A, axis, transform_A);
            auto [projections_B_min, projections_B_max] = polygon_projection(polygon_B, axis, transform_B);

            if (projections_A_max < projections_B_min || projections_B_max < projections_A_min)
                return std::nullopt;

            float min_depth = std::min(projections_A_max - projections_B_min, projections_B_max - projections_A_min);

            if (min_depth < total_min_depth)
            {
                total_min_depth = min_depth;

                if (utils::dot(polygon_B_position_rotated - polygon_A_position_rotated, axis) < 0.f)
                    normal = -axis;
                else
                    normal = axis;
            }
        }

        return { { 
            {}, 
            normal, total_min_depth,
            fminf(polygon_A_raw->get_restitution(), polygon_B_raw->get_restitution())
        } };
    }

    std::optional<CollisionInfo> CollisionSolver::polygon_circle_collision(std::shared_ptr<Fixture> polygon_raw, std::shared_ptr<Fixture> circle_raw, 
                                                                           const Transform& transform_A, const Transform& transform_B) const
    {
        // Convert pointers
        auto polygon = std::dynamic_pointer_cast<PolygonShape>(polygon_raw->get_shape());
        auto circle  = std::dynamic_pointer_cast<CircleShape> (circle_raw ->get_shape());

        // --- //

        auto& vertices = polygon->get_vertices();

        auto polygon_position = polygon->get_position();
        auto circle_position  = circle ->get_position();

        auto polygon_position_rotated = physics::rotate_and_move_point(polygon_position, transform_A);
        auto circle_position_rotated  = physics::rotate_and_move_point(circle_position,  transform_B);

        float total_min_depth = std::numeric_limits<float>::max();
        sf::Vector2f normal{};

        auto count = (int32_t)vertices.size();
        for (int32_t i = 0; i < count; ++i)
        {
            auto i_and_one = (i == count - 1) ? 0 : i + 1;
            auto point_A = physics::rotate_and_move_point(polygon_position + vertices.at(i),         transform_A);
            auto point_B = physics::rotate_and_move_point(polygon_position + vertices.at(i_and_one), transform_A);

            auto edge = point_B - point_A;
            auto axis = utils::normalize(sf::Vector2f(-edge.y, edge.x));

            auto [projections_A_min, projections_A_max] = polygon_projection(polygon, axis, transform_A);
            auto [projections_B_min, projections_B_max] = circle_projection (circle,  axis, transform_B);

            if (projections_A_max < projections_B_min || projections_B_max < projections_A_min)
                return std::nullopt;

            float min_depth = std::min(projections_A_max - projections_B_min, projections_B_max - projections_A_min);

            if (min_depth < total_min_depth)
            {
                total_min_depth = min_depth;

                if (utils::dot(circle_position_rotated - polygon_position_rotated, axis) < 0.f)
                    normal = -axis;
                else
                    normal = axis;
            }
        }

        auto closest_point = circle_polygon_closest_point(polygon, circle, transform_A, transform_B);

        auto axis = utils::normalize(closest_point - circle_position_rotated);

        auto [projections_A_min, projections_A_max] = polygon_projection(polygon, axis, transform_A);
        auto [projections_B_min, projections_B_max] = circle_projection (circle,  axis, transform_B);

        if (projections_A_max < projections_B_min || projections_B_max < projections_A_min)
            return std::nullopt;

        float min_depth = std::min(projections_A_max - projections_B_min, projections_B_max - projections_A_min);

        if (min_depth < total_min_depth)
        {
            total_min_depth = min_depth;

            if (utils::dot(circle_position_rotated - polygon_position_rotated, axis) < 0.f)
                normal = -axis;
            else
                normal = axis;
        }

        return { { 
            {}, 
            normal, total_min_depth,
            fminf(polygon_raw->get_restitution(), circle_raw->get_restitution())
        } };
    }

    std::optional<CollisionInfo> CollisionSolver::circle_polygon_collision(std::shared_ptr<Fixture> circle_raw, std::shared_ptr<Fixture> polygon_raw, 
                                                                           const Transform& transform_A, const Transform& transform_B) const
    {
        auto result = polygon_circle_collision(polygon_raw, circle_raw, transform_B, transform_A);

        if (result)
            result->collision_normal = -result->collision_normal;

        return result;
    }

    // --- Collision points
    void CollisionSolver::write_collision_points(CollisionInfo& collision, std::shared_ptr<Fixture> fixture_A, std::shared_ptr<Fixture> fixture_B,
                                                 const Transform& transform_A, const Transform& transform_B)
    {
        auto& shape_A = fixture_A->get_shape();
        auto& shape_B = fixture_B->get_shape();

        switch (shape_A->get_shape()) {
        case ShapeType::Rectangle:
            switch (shape_B->get_shape()) {
            case ShapeType::Rectangle: collision.contact_info = polygons_collision_points       (shape_A, shape_B, transform_A, transform_B); break;
            case ShapeType::Circle:    collision.contact_info = circle_polygon_collision_points (shape_A, shape_B, transform_A, transform_B); break;
            default: break;
            } break;
        case ShapeType::Circle:
            switch (shape_B->get_shape()) {
            case ShapeType::Rectangle: collision.contact_info = circle_polygon_collision_points (shape_B, shape_A, transform_B, transform_A); break;
            case ShapeType::Circle:    collision.contact_info = circles_collision_points        (shape_A, shape_B, transform_A, transform_B); break;
            default: break;
            } break;
        default: break;
        }
    }

    ContactInfo CollisionSolver::circles_collision_points(std::shared_ptr<Shape> circle_A_raw, std::shared_ptr<Shape> circle_B_raw,
                                                          const Transform& transform_A, const Transform& transform_B) const
    {
        // Convert pointers
        auto circle_A = std::dynamic_pointer_cast<CircleShape>(circle_A_raw);
        auto circle_B = std::dynamic_pointer_cast<CircleShape>(circle_B_raw);

        // Prepare data
        auto position_A = physics::rotate_and_move_point(circle_A->get_position(), transform_A);
        auto position_B = physics::rotate_and_move_point(circle_B->get_position(), transform_B);

        auto radius_A = circle_A->get_radius();
        auto radius_B = circle_B->get_radius();

        // --- //
        ContactInfo contact{
            { (position_A.x * radius_B + position_B.x * radius_A) / (radius_A + radius_B),
              (position_A.y * radius_B + position_B.y * radius_A) / (radius_A + radius_B) },
            {}, 1
        };

#ifdef DEBUG
        debug_entities.push_back(graphics::DebugDraw{ graphics::DebugDraw::Circle, contact.collision_point_1, sf::Color::Blue, 4, 0, {} });
#endif // DEBUG

        return contact;
    }

    ContactInfo CollisionSolver::polygons_collision_points(std::shared_ptr<Shape> polygon_A_raw, std::shared_ptr<Shape> polygon_B_raw,
                                                           const Transform& transform_A, const Transform& transform_B) const
    {
        // Convert pointers
        auto polygon_A = std::dynamic_pointer_cast<PolygonShape>(polygon_A_raw);
        auto polygon_B = std::dynamic_pointer_cast<PolygonShape>(polygon_B_raw);

        // --- //
        auto polygon_A_position = polygon_A->get_position();
        auto polygon_B_position = polygon_B->get_position();

        auto polygon_A_position_rotated = physics::rotate_and_move_point(polygon_A_position, transform_A);
        auto polygon_B_position_rotated = physics::rotate_and_move_point(polygon_B_position, transform_B);

        auto& vertices_A = polygon_A->get_vertices();
        auto& vertices_B = polygon_B->get_vertices();

        // --- //

        float min_distance = std::numeric_limits<float>::max();
        ContactInfo contacts{};

        auto count_A = (int32_t)vertices_A.size();
        auto count_B = (int32_t)vertices_B.size();


        for (int32_t j = 0; j < count_B; ++j)
        {
            auto j_and_one = (j == count_B - 1) ? 0 : j + 1;

            auto point_B_A = physics::rotate_and_move_point(polygon_B_position + vertices_B.at(j), transform_B);
            auto point_B_B = physics::rotate_and_move_point(polygon_B_position + vertices_B.at(j_and_one), transform_B);

            for (int32_t i = 0; i < count_A; ++i)
            {
                auto i_and_one = (i == count_A - 1) ? 0 : i + 1;

                auto point_A_A = physics::rotate_and_move_point(polygon_A_position + vertices_A.at(i), transform_A);
                auto point_A_B = physics::rotate_and_move_point(polygon_A_position + vertices_A.at(i_and_one), transform_A);

                auto [distance_squared_A, contact_point_A] = physics::point_segment_distance_squared(point_A_A, point_B_A, point_B_B);
                auto [distance_squared_B, contact_point_B] = physics::point_segment_distance_squared(point_B_A, point_A_A, point_A_B);


                if (distance_squared_A < min_distance)
                {
                    min_distance = distance_squared_A;
                    contacts.collision_point_1 = contact_point_A;
                    contacts.collision_point_cnt = 1;
                }
                else if (physics::almost_equal(distance_squared_A, min_distance))
                {
                    if (!physics::almost_equal(contact_point_A, contacts.collision_point_1))
                    {
                        contacts.collision_point_2 = contact_point_A;
                        contacts.collision_point_cnt = 2;
                    }
                }

                if (distance_squared_B < min_distance)
                {
                    min_distance = distance_squared_B;
                    contacts.collision_point_1 = contact_point_B;
                    contacts.collision_point_cnt = 1;
                }
                else if (physics::almost_equal(distance_squared_B, min_distance))
                {
                    if (!physics::almost_equal(contact_point_B, contacts.collision_point_1))
                    {
                        contacts.collision_point_2 = contact_point_B;
                        contacts.collision_point_cnt = 2;
                    }
                }
            }
        }

#ifdef DEBUG
        debug_entities.push_back(graphics::DebugDraw{ graphics::DebugDraw::Circle, contacts.collision_point_1, sf::Color::Blue, 4, 0, {} });

        if (contacts.collision_point_cnt == 2)
            debug_entities.push_back(graphics::DebugDraw{ graphics::DebugDraw::Circle, contacts.collision_point_2, sf::Color::Blue, 4, 0, {} });
#endif // DEBUG

        return contacts;
    }

    ContactInfo CollisionSolver::circle_polygon_collision_points(std::shared_ptr<Shape> polygon_raw, std::shared_ptr<Shape> circle_raw,
                                                                 const Transform& transform_A, const Transform& transform_B) const
    {
        // Convert pointers
        auto polygon = std::dynamic_pointer_cast<PolygonShape>(polygon_raw);
        auto circle  = std::dynamic_pointer_cast<CircleShape> (circle_raw );

        // --- //
        auto polygon_position = polygon->get_position();
        auto circle_position  = circle ->get_position();

        auto polygon_position_rotated = physics::rotate_and_move_point(polygon_position, transform_A);
        auto circle_position_rotated  = physics::rotate_and_move_point(circle_position,  transform_B);

        auto& vertices = polygon->get_vertices();

        // --- //
        float min_distance = std::numeric_limits<float>::max();
        ContactInfo contact{};

        auto count = (int32_t)vertices.size();
        for (int32_t i = 0; i < count; ++i)
        {
            auto i_and_one = (i == count - 1) ? 0 : i + 1;

            auto point_A = physics::rotate_and_move_point(polygon_position + vertices.at(i), transform_A);
            auto point_B = physics::rotate_and_move_point(polygon_position + vertices.at(i_and_one), transform_A);

            auto [distance_squared, contact_point] = physics::point_segment_distance_squared(circle_position_rotated, point_A, point_B);

            if (distance_squared < min_distance)
            {
                min_distance = distance_squared;
                contact.collision_point_1 = contact_point;
                contact.collision_point_cnt = 1;
            }
        }

#ifdef DEBUG
        debug_entities.push_back(graphics::DebugDraw{ graphics::DebugDraw::Circle, contact.collision_point_1, sf::Color::Blue, 4, 0, {} });
#endif // DEBUG

        return contact;
    }


    // --- Collision resolution
    void CollisionSolver::separate_bodies(const CollisionInfo& collision, std::shared_ptr<RigidBody> body_A, std::shared_ptr<RigidBody> body_B) const
    {
        auto fixated_A = body_A->get_linear_fixation();
        auto fixated_B = body_B->get_linear_fixation();

        sf::Vector2f resolve_coefficients_A{ 0.5f, 0.5f };
        sf::Vector2f resolve_coefficients_B{ 0.5f, 0.5f };

        if (fixated_A.first)
        {
            resolve_coefficients_A.x = 0.f; // First  x stands
            resolve_coefficients_B.x = 1.f; // Second x gets all movement
        }
        if (fixated_B.first)
        {
            resolve_coefficients_A.x *= 2;   // First  x get all movement (0.5 * 2 = 1) or stands (0 * 2 = 0)
            resolve_coefficients_B.x  = 0.f; // Second x stands
        }

        if (fixated_A.second)
        {
            resolve_coefficients_A.y = 0.f; // First  y stands
            resolve_coefficients_B.y = 1.f; // Second y gets all movement
        }
        if (fixated_B.second)
        {
            resolve_coefficients_A.y *= 2;   // First  y get all movement (0.5 * 2 = 1) or stands (0 * 2 = 0)
            resolve_coefficients_B.y  = 0.f; // Second y stands
        }

        sf::Vector2f normal_A{ collision.collision_normal.x * resolve_coefficients_A.x, collision.collision_normal.y * resolve_coefficients_A.y };
        sf::Vector2f normal_B{ collision.collision_normal.x * resolve_coefficients_B.x, collision.collision_normal.y * resolve_coefficients_B.y };

        body_A->move(-normal_A * collision.depth);
        body_B->move( normal_B * collision.depth);
    }

    void CollisionSolver::resolve_collision(const CollisionInfo& collision, std::shared_ptr<RigidBody> body_A, std::shared_ptr<RigidBody> body_B) const
    {   
        auto speed_A = body_A->get_linear_speed();
        auto speed_B = body_B->get_linear_speed();

        auto fixated_A = body_A->get_linear_fixation();
        auto fixated_B = body_B->get_linear_fixation();

        auto relative_speed = speed_B - speed_A;

        if (utils::dot(relative_speed, collision.collision_normal) > 0.f)
            return;

        sf::Vector2f inv_mass_A{
            (fixated_A.first  ? 0.f : body_A->get_inv_mass()),
            (fixated_A.second ? 0.f : body_A->get_inv_mass())
        };
        sf::Vector2f inv_mass_B{
            (fixated_B.first  ? 0.f : body_B->get_inv_mass()),
            (fixated_B.second ? 0.f : body_B->get_inv_mass())
        };

        float nominator = -(1 + collision.elasticity) * utils::dot(relative_speed, collision.collision_normal);

        sf::Vector2f I{
            (inv_mass_A.x + inv_mass_B.x) == 0.f ? 0 : nominator / (inv_mass_A.x + inv_mass_B.x),
            (inv_mass_A.y + inv_mass_B.y) == 0.f ? 0 : nominator / (inv_mass_A.y + inv_mass_B.y)
        };

        speed_A.x -= I.x * body_A->get_inv_mass() * collision.collision_normal.x * (!fixated_A.first);
        speed_A.y -= I.y * body_A->get_inv_mass() * collision.collision_normal.y * (!fixated_A.second);
        speed_B.x += I.x * body_B->get_inv_mass() * collision.collision_normal.x * (!fixated_B.first);
        speed_B.y += I.y * body_B->get_inv_mass() * collision.collision_normal.y * (!fixated_B.second);

        body_A->set_linear_speed(speed_A);
        body_B->set_linear_speed(speed_B);
    }


    // --- Aditional methods
    std::pair<float, float> CollisionSolver::polygon_projection(std::shared_ptr<PolygonShape> polygon, const sf::Vector2f& axis, const Transform& transform) const
    {
        float min_projection = std::numeric_limits<float>::max();
        float max_projection = std::numeric_limits<float>::lowest();

        auto& vertices = polygon->get_vertices();

        auto polygon_position = polygon->get_position();

        for (auto& vertex : vertices)
        {
            float projection = utils::dot(physics::rotate_and_move_point(polygon_position + vertex, transform), axis);

            min_projection = std::min(min_projection, projection);
            max_projection = std::max(max_projection, projection);
        }

        return { min_projection, max_projection };
    }

    std::pair<float, float> CollisionSolver::circle_projection(std::shared_ptr<CircleShape> circle, const sf::Vector2f& axis, const Transform& transform) const
    {
        float central = utils::dot(physics::rotate_and_move_point(circle->get_position(), transform), axis);

        float min_projection = central - circle->get_radius();
        float max_projection = central + circle->get_radius();

        return { min_projection, max_projection };
    }


    sf::Vector2f CollisionSolver::circle_polygon_closest_point(std::shared_ptr<PolygonShape> polygon, std::shared_ptr<CircleShape> circle, Transform transform_A, Transform transform_B) const
    {
        sf::Vector2f closest_point{};
        float min_distance = std::numeric_limits<float>::max();

        auto polygon_position = polygon->get_position();

        auto circle_position_rotated = physics::rotate_and_move_point(circle->get_position(), transform_B);

        for (auto& vertex : polygon->get_vertices())
        {
            auto rotated_vertex = physics::rotate_and_move_point(polygon_position + vertex, transform_A);

            auto distance_squared = utils::distance_squared(circle_position_rotated, rotated_vertex);

            if (distance_squared < min_distance)
            {
                closest_point = rotated_vertex;
                min_distance = distance_squared;
            }
        }

        return closest_point;
    }

} // namespace physics
