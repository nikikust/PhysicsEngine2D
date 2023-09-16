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
            normal / utils::pif(normal),
            radius_A + radius_B - distance
        }};
    }
    else
        return std::nullopt;
}
std::optional<CollisionInfo> rectangles_collision(std::shared_ptr<Shape> rectangle_A_raw, std::shared_ptr<Shape> rectangle_B_raw)
{


    return std::nullopt;
}
std::optional<CollisionInfo> rectangle_circle_collision(std::shared_ptr<Shape> rectangle_raw, std::shared_ptr<Shape> circle_raw)
{
    // Convert pointers
    auto rectangle = std::dynamic_pointer_cast<RectangleShape>(rectangle_raw);
    auto circle    = std::dynamic_pointer_cast<CircleShape>   (circle_raw);

    // Prepare rotated coordinates
    CircleShape circle_rotated = *circle;

    circle_rotated.move  (-rectangle->get_position());
    circle_rotated.rotate( rectangle->get_angle   ());

    circle_rotated.set_position(utils::rotate_point(circle_rotated.get_position(), rectangle->get_angle()));

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
        closest_point = utils::rotate_point(closest_point, -rectangle->get_angle()) + rectangle->get_position();
        
        auto normal = circle->get_position() - closest_point;

        float depth = circle->get_radius() - utils::pif(circle->get_position() - closest_point);

        return {{
            closest_point,
            normal / utils::pif(normal),
            depth
        }};
    }
    else
        return std::nullopt;
}
