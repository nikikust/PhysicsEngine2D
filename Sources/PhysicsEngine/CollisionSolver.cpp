#include "../../Include/PhysicsEngine/CollisionSolver.h"


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
    shape_A->move(-collision.collision_normal * collision.depth / 2.f);
    shape_B->move( collision.collision_normal * collision.depth / 2.f);
}
void CollisionSolver::resolve_collision(const CollisionInfo& collision, std::shared_ptr<Shape> shape_A, std::shared_ptr<Shape> shape_B)
{
    resolve_collision_simple(collision, shape_A, shape_B);

    auto  speed_A = shape_A->get_linear_speed();
    auto  speed_B = shape_B->get_linear_speed();

    auto  relative_speed = speed_B - speed_A;

    auto& material_A = data_storage_.scene_data.materials.at(shape_A->get_material_id());
    auto& material_B = data_storage_.scene_data.materials.at(shape_B->get_material_id());

    float e = fminf(material_A->get_elasticity(), material_B->get_elasticity());

    float I = -(1 + e) * utils::dot(relative_speed, collision.collision_normal) / (1 / shape_A->get_mass() + 1 / shape_B->get_mass());

    speed_A -= I / shape_A->get_mass() * collision.collision_normal;
    speed_B += I / shape_A->get_mass() * collision.collision_normal;

    shape_A->set_linear_speed(speed_A);
    shape_B->set_linear_speed(speed_B);
}
