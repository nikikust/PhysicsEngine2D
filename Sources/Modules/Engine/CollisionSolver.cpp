#include "../../../Include/Modules/Engine/CollisionSolver.h"


std::optional<sf::Vector2f> circles_collision(const CircleShape& circle_A, const CircleShape& circle_B)
{
    return std::nullopt;
}
std::optional<sf::Vector2f> rectangles_collision(const RectangleShape& rectangle_A, const RectangleShape& rectangle_B)
{
    return std::nullopt;
}
std::optional<sf::Vector2f> rectangle_circle_collision(const RectangleShape& rectangle, const CircleShape& circle)
{
    // Prepare rotated coordinates
    CircleShape circle_rotated = circle;

    circle_rotated.move  (-rectangle.get_position());
    circle_rotated.rotate( rectangle.get_angle   ());

    circle_rotated.set_position(utils::rotate_point(circle_rotated.get_position(), rectangle.get_angle()));

    // Find closest point
    auto circle_position      = circle_rotated.get_position();
    auto rectangle_half_size  = rectangle     .get_size() / 2.f;

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

    if (distance < circle.get_radius())
    {
        closest_point = utils::rotate_point(closest_point, -rectangle.get_angle());
        
        return { closest_point + rectangle.get_position() };
    }
    else
        return std::nullopt;
}
