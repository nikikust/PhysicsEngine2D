#include "../../Include/PhysicsEngine/CollisionSolver.h"


namespace physics
{
    CollisionSolver::CollisionSolver(DataStorage& data_storage)
        : data_storage_(data_storage)
    {
    }

    std::optional<CollisionInfo> CollisionSolver::circles_collision(std::shared_ptr<Shape> circle_A_raw, std::shared_ptr<Shape> circle_B_raw)
    {
        // Convert pointers
        auto circle_A = std::dynamic_pointer_cast<CircleShape>(circle_A_raw);
        auto circle_B = std::dynamic_pointer_cast<CircleShape>(circle_B_raw);

        // Prepare data
        auto position_A = circle_A->get_position();
        auto position_B = circle_B->get_position();

        auto radius_A = circle_A->get_radius();
        auto radius_B = circle_B->get_radius();

        auto distance = utils::pif(position_B - position_A);

        if (distance < radius_A + radius_B)
        {
            auto normal = position_B - position_A;

            return { {
                sf::Vector2f{ (position_A.x * radius_B + position_B.x * radius_A) / (radius_A + radius_B),
                              (position_A.y * radius_B + position_B.y * radius_A) / (radius_A + radius_B) },
                utils::normalize(normal),
                radius_A + radius_B - distance
            } };
        }
        else
            return std::nullopt;
    }
    std::optional<CollisionInfo> CollisionSolver::polygons_collision(std::shared_ptr<Shape> polygon_A_raw, std::shared_ptr<Shape> polygon_B_raw)
    {
        // Convert pointers
        auto polygon_A = std::dynamic_pointer_cast<PolygonShape>(polygon_A_raw);
        auto polygon_B = std::dynamic_pointer_cast<PolygonShape>(polygon_B_raw);

        // --- //

        auto& vertices_A = polygon_A->get_vertices();
        auto& vertices_B = polygon_B->get_vertices();

        float total_min_depth = std::numeric_limits<float>::max();
        sf::Vector2f normal{};


        for (int32_t i = 0; i < vertices_A.size(); ++i)
        {
            auto point_A = utils::rotate_point(vertices_A.at(i), polygon_A->get_angle());
            auto point_B = utils::rotate_point(vertices_A.at((i + 1) % vertices_A.size()), polygon_A->get_angle());

            auto edge = point_B - point_A;
            auto axis = utils::normalize(sf::Vector2f(-edge.y, edge.x));

            auto [projections_A_min, projections_A_max] = polygon_projection(polygon_A, axis);
            auto [projections_B_min, projections_B_max] = polygon_projection(polygon_B, axis);

            if (projections_A_max < projections_B_min || projections_B_max < projections_A_min)
                return std::nullopt;

            float min_depth = std::min(projections_A_max - projections_B_min, projections_B_max - projections_A_min);

            if (min_depth < total_min_depth)
            {
                total_min_depth = min_depth;

                if (utils::dot(polygon_B->get_position() - polygon_A->get_position(), axis) < 0.f)
                    normal = -axis;
                else
                    normal = axis;
            }
        }

        for (int32_t i = 0; i < vertices_B.size(); ++i)
        {
            auto point_A = utils::rotate_point(vertices_B.at(i), polygon_B->get_angle());
            auto point_B = utils::rotate_point(vertices_B.at((i + 1) % vertices_B.size()), polygon_B->get_angle());

            auto edge = point_B - point_A;
            auto axis = utils::normalize(sf::Vector2f(-edge.y, edge.x));

            auto [projections_A_min, projections_A_max] = polygon_projection(polygon_A, axis);
            auto [projections_B_min, projections_B_max] = polygon_projection(polygon_B, axis);

            if (projections_A_max < projections_B_min || projections_B_max < projections_A_min)
                return std::nullopt;

            float min_depth = std::min(projections_A_max - projections_B_min, projections_B_max - projections_A_min);

            if (min_depth < total_min_depth)
            {
                total_min_depth = min_depth;

                if (utils::dot(polygon_B->get_position() - polygon_A->get_position(), axis) < 0.f)
                    normal = -axis;
                else
                    normal = axis;
            }
        }

        return { { polygon_A->get_position(), normal, total_min_depth} };
    }
    std::optional<CollisionInfo> CollisionSolver::polygon_circle_collision(std::shared_ptr<Shape> polygon_raw, std::shared_ptr<Shape> circle_raw)
    {
        // Convert pointers
        auto polygon = std::dynamic_pointer_cast<PolygonShape>(polygon_raw);
        auto circle = std::dynamic_pointer_cast<CircleShape> (circle_raw);

        // --- //

        auto& vertices = polygon->get_vertices();

        float total_min_depth = std::numeric_limits<float>::max();
        sf::Vector2f normal{};


        for (int32_t i = 0; i < vertices.size(); ++i)
        {
            auto point_A = utils::rotate_point(vertices.at(i), polygon->get_angle());
            auto point_B = utils::rotate_point(vertices.at((i + 1) % vertices.size()), polygon->get_angle());

            auto edge = point_B - point_A;
            auto axis = utils::normalize(sf::Vector2f(-edge.y, edge.x));

            auto [projections_A_min, projections_A_max] = polygon_projection(polygon, axis);
            auto [projections_B_min, projections_B_max] = circle_projection(circle, axis);

            if (projections_A_max < projections_B_min || projections_B_max < projections_A_min)
                return std::nullopt;

            float min_depth = std::min(projections_A_max - projections_B_min, projections_B_max - projections_A_min);

            if (min_depth < total_min_depth)
            {
                total_min_depth = min_depth;

                if (utils::dot(circle->get_position() - polygon->get_position(), axis) < 0.f)
                    normal = -axis;
                else
                    normal = axis;
            }
        }

        auto closest_point = circle_polygon_closest_point(polygon, circle);

        auto axis = utils::normalize(closest_point - circle->get_position());

        auto [projections_A_min, projections_A_max] = polygon_projection(polygon, axis);
        auto [projections_B_min, projections_B_max] = circle_projection(circle, axis);

        if (projections_A_max < projections_B_min || projections_B_max < projections_A_min)
            return std::nullopt;

        float min_depth = std::min(projections_A_max - projections_B_min, projections_B_max - projections_A_min);

        if (min_depth < total_min_depth)
        {
            total_min_depth = min_depth;

            if (utils::dot(circle->get_position() - polygon->get_position(), axis) < 0.f)
                normal = -axis;
            else
                normal = axis;
        }

        return { { polygon->get_position(), normal, total_min_depth} };
    }
    std::optional<CollisionInfo> CollisionSolver::circle_polygon_collision(std::shared_ptr<Shape> circle_raw, std::shared_ptr<Shape> polygon_raw)
    {
        auto result = polygon_circle_collision(polygon_raw, circle_raw);

        if (result)
            result->collision_normal = -result->collision_normal;

        return result;
    }

    std::pair<float, float> CollisionSolver::polygon_projection(std::shared_ptr<PolygonShape> polygon, const sf::Vector2f& axis)
    {
        float min_projection = std::numeric_limits<float>::max();
        float max_projection = std::numeric_limits<float>::lowest();

        auto& vertices = polygon->get_vertices();
        auto  position = polygon->get_position();

        for (auto& vertex : vertices)
        {
            float projection = utils::dot(utils::rotate_point(vertex, polygon->get_angle()) + position, axis);

            min_projection = std::min(min_projection, projection);
            max_projection = std::max(max_projection, projection);
        }

        return { min_projection, max_projection };
    }
    std::pair<float, float> CollisionSolver::circle_projection(std::shared_ptr<CircleShape> circle, const sf::Vector2f& axis)
    {
        float central = utils::dot(circle->get_position(), axis);

        float min_projection = central - circle->get_radius();
        float max_projection = central + circle->get_radius();

        return { min_projection, max_projection };
    }

    sf::Vector2f CollisionSolver::circle_polygon_closest_point(std::shared_ptr<PolygonShape> polygon, std::shared_ptr<CircleShape> circle)
    {
        sf::Vector2f closest_point{};
        float min_distance = std::numeric_limits<float>::max();

        auto polygon_position = polygon->get_position();
        auto circle_position = circle->get_position();

        for (auto& vertex : polygon->get_vertices())
        {
            auto rotated_vertex = utils::rotate_point(vertex, polygon->get_angle());

            auto distance = utils::pif(rotated_vertex + polygon_position - circle_position);

            if (distance < min_distance)
            {
                closest_point = rotated_vertex + polygon_position;
                min_distance = distance;
            }
        }

        return closest_point;
    }

    void CollisionSolver::resolve_collision_simple(const CollisionInfo& collision, std::shared_ptr<Shape> shape_A, std::shared_ptr<Shape> shape_B)
    {
        auto fixated_A = shape_A->get_linear_fixation();
        auto fixated_B = shape_B->get_linear_fixation();

        sf::Vector2f resolve_coefficients_x{ 0.5f, 0.5f };
        sf::Vector2f resolve_coefficients_y{ 0.5f, 0.5f };

        if (fixated_A.first)
        {
            resolve_coefficients_x.x = 0.f; // First  x stands
            resolve_coefficients_x.y = 1.f; // Second x gets all movement
        }
        if (fixated_B.first)
        {
            resolve_coefficients_x.x *= 2;   // First  x get all movement (0.5 * 2 = 1) or stands (0 * 2 = 0)
            resolve_coefficients_x.x  = 0.f; // Second x stands
        }

        if (fixated_A.second)
        {
            resolve_coefficients_y.x = 0.f; // First  y stands
            resolve_coefficients_y.y = 1.f; // Second y gets all movement
        }
        if (fixated_B.second)
        {
            resolve_coefficients_y.x *= 2;   // First  y get all movement (0.5 * 2 = 1) or stands (0 * 2 = 0)
            resolve_coefficients_y.x  = 0.f; // Second y stands
        }

        sf::Vector2f normal_A{ collision.collision_normal.x * resolve_coefficients_x.x, collision.collision_normal.y * resolve_coefficients_y.x };
        sf::Vector2f normal_B{ collision.collision_normal.x * resolve_coefficients_x.y, collision.collision_normal.y * resolve_coefficients_y.y };

        shape_A->move(-normal_A * collision.depth);
        shape_B->move( normal_B * collision.depth);
    }
    void CollisionSolver::resolve_collision(const CollisionInfo& collision, std::shared_ptr<Shape> shape_A, std::shared_ptr<Shape> shape_B)
    {
        resolve_collision_simple(collision, shape_A, shape_B);

        auto speed_A = shape_A->get_linear_speed();
        auto speed_B = shape_B->get_linear_speed();

        auto fixated_A = shape_A->get_linear_fixation();
        auto fixated_B = shape_B->get_linear_fixation();

        auto relative_speed = speed_B - speed_A;

        if (utils::dot(relative_speed, collision.collision_normal) > 0.f)
            return;

        auto& material_A = data_storage_.scene_data.materials.at(shape_A->get_material_id());
        auto& material_B = data_storage_.scene_data.materials.at(shape_B->get_material_id());

        float e = fminf(material_A->get_elasticity(), material_B->get_elasticity());

        sf::Vector2f inv_mass_A{
            (fixated_A.first  ? 0.f : 1 / shape_A->get_mass()),
            (fixated_A.second ? 0.f : 1 / shape_A->get_mass())
        };
        sf::Vector2f inv_mass_B{
            (fixated_B.first  ? 0.f : 1 / shape_B->get_mass()),
            (fixated_B.second ? 0.f : 1 / shape_B->get_mass())
        };

        float nominator = -(1 + e) * utils::dot(relative_speed, collision.collision_normal);

        sf::Vector2f I{
            (inv_mass_A.x + inv_mass_B.x) == 0.f ? 0 : nominator / (inv_mass_A.x + inv_mass_B.x),
            (inv_mass_A.y + inv_mass_B.y) == 0.f ? 0 : nominator / (inv_mass_A.y + inv_mass_B.y)
        };

        speed_A.x -= I.x / shape_A->get_mass() * collision.collision_normal.x * (!fixated_A.first);
        speed_A.y -= I.y / shape_B->get_mass() * collision.collision_normal.y * (!fixated_A.second);
        speed_B.x += I.x / shape_A->get_mass() * collision.collision_normal.x * (!fixated_B.first);
        speed_B.y += I.y / shape_B->get_mass() * collision.collision_normal.y * (!fixated_B.second);

        shape_A->set_linear_speed(speed_A);
        shape_B->set_linear_speed(speed_B);
    }
} // namespace physics
