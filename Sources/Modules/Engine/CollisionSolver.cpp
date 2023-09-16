#include "../../../Include/Modules/Engine/CollisionSolver.h"


std::optional<CollisionInfo> circles_collision(std::shared_ptr<Shape> circle_A_raw, std::shared_ptr<Shape> circle_B_raw)
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

        return {{
            sf::Vector2f{ (position_A.x * radius_B + position_B.x * radius_A) / (radius_A + radius_B),
                          (position_A.y * radius_B + position_B.y * radius_A) / (radius_A + radius_B) },
            utils::normalize(normal),
            radius_A + radius_B - distance
        }};
    }
    else
        return std::nullopt;
}
std::optional<CollisionInfo> polygons_collision(std::shared_ptr<Shape> polygon_A_raw, std::shared_ptr<Shape> polygon_B_raw)
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
        auto point_A = utils::rotate_point(vertices_A.at(i),                           polygon_A->get_angle());
        auto point_B = utils::rotate_point(vertices_A.at((i + 1) % vertices_A.size()), polygon_A->get_angle());

        auto edge = point_B - point_A;
        auto axis = utils::normalize(sf::Vector2f(-edge.y, edge.x));

        auto [projections_A_min, projections_A_max] = min_max_projection(polygon_A, axis);
        auto [projections_B_min, projections_B_max] = min_max_projection(polygon_B, axis);

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
        auto point_A = utils::rotate_point(vertices_B.at(i),                           polygon_B->get_angle());
        auto point_B = utils::rotate_point(vertices_B.at((i + 1) % vertices_B.size()), polygon_B->get_angle());

        auto edge = point_B - point_A;
        auto axis = utils::normalize(sf::Vector2f(-edge.y, edge.x));

        auto [projections_A_min, projections_A_max] = min_max_projection(polygon_A, axis);
        auto [projections_B_min, projections_B_max] = min_max_projection(polygon_B, axis);

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
std::optional<CollisionInfo> polygon_circle_collision(std::shared_ptr<Shape> rectangle_raw, std::shared_ptr<Shape> circle_raw)
{
    /*
    // Convert pointers
    auto rectangle = std::dynamic_pointer_cast<PolygonShape>(rectangle_raw);
    auto circle    = std::dynamic_pointer_cast<CircleShape>   (circle_raw);

    // Prepare rotated coordinates
    CircleShape circle_rotated = *circle;

    circle_rotated.move  (-rectangle->get_position());
    circle_rotated.rotate( rectangle->get_angle   ());

    circle_rotated.set_position(utils::rotate_point(circle_rotated.get_position(), -rectangle->get_angle()));

    // Find closest point
    auto circle_position      = circle_rotated.get_position();
    auto rectangle_half_size  = rectangle    ->get_size() / 2.f;

    sf::Vector2f closest_point{};

    if (circle_position.x <= -rectangle_half_size.x)
        closest_point.x = -rectangle_half_size.x;
    else if (circle_position.x >= rectangle_half_size.x)
        closest_point.x = rectangle_half_size.x;
    else
        closest_point.x = circle_position.x;

    if (circle_position.y <= -rectangle_half_size.y)
        closest_point.y = -rectangle_half_size.y;
    else if (circle_position.y >= rectangle_half_size.y)
        closest_point.y = rectangle_half_size.y;
    else
        closest_point.y = circle_position.y;

    // Determine collision
    float distance = utils::pif(circle_position - closest_point);

    if (distance < circle->get_radius())
    {
        closest_point = utils::rotate_point(closest_point, rectangle->get_angle()) + rectangle->get_position();
        
        auto normal = circle->get_position() - closest_point;

        float depth = circle->get_radius() - utils::pif(circle->get_position() - closest_point);

        return {{
            closest_point,
            utils::normalize(normal),
            depth
        }};
    }
    else*/
        return std::nullopt;
}
std::optional<CollisionInfo> circle_polygon_collision(std::shared_ptr<Shape> circle_raw, std::shared_ptr<Shape> rectangle_raw)
{
    auto result = polygon_circle_collision(rectangle_raw, circle_raw);

    if (result)
        result->collision_normal = -result->collision_normal;

    return result;
}

std::pair<float, float> min_max_projection(std::shared_ptr<PolygonShape> polygon, const sf::Vector2f& axis)
{
    float min_projection = std::numeric_limits<float>::max();
    float max_projection = std::numeric_limits<float>::min();

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
