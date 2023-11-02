#include <GameEngine/PhysicsEngine/Shapes/PolygonShape.h>


namespace physics
{
    PolygonShape::PolygonShape(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& position)
        : Shape(ShapeType::Polygon, position)
    {
        set_vertices(vertices);
    }

    // --- //

    PhysicalData PolygonShape::calculate_physical_data(float density) const
    {
        // Accumulate the following values
        float area = 0.0;
        float mass = 0.0;

        sf::Vector2f center = { 0.0, 0.0 };
        float mmoi = 0.0;

        // Take each vertex pair starting from the last-first vertex in order to consider all sides.
        auto count = (int32_t)vertices_.size();

        auto& point = vertices_.front();

        for (int32_t i = 0; i < count; ++i)
        {
            int32_t i_and_one = (i + 1 == count) ? 0 : i + 1;

            sf::Vector2f A = vertices_.at(i);
            sf::Vector2f B = vertices_.at(i_and_one);

            sf::Vector2f edge_A = A - point;
            sf::Vector2f edge_B = B - point;

            float area_step = physics::triangle_area(edge_A, edge_B);
            float mass_step = density * area_step;
            sf::Vector2f center_step = physics::triangle_center(edge_A, edge_B);

            float mmoi_step = physics::triangle_mmoi(edge_A, edge_B, mass_step);

            if (mass_step == 0.f)
                continue;

            area += area_step;
            center = (mass * center + mass_step * center_step) / (mass + mass_step);
            mass += mass_step;
            mmoi += mmoi_step;
        }

        // Transfer mass moment of inertia from the origin to the center of mass
        mmoi -= mass * utils::dot(center, center);

        center += point;

        return PhysicalData{ area, mass, (mass > 0.f) ? 1.f / mass : 0.f, center, mmoi };
    }

    bool PolygonShape::cast_ray(const Ray& ray, const Transform& transform, RayHitInfo& output) const
    {
        // Put ray to the polygon's space
        Ray rotated_ray{ 
            physics::rotate_point_T(ray.origin - transform.position, transform.rotation) - position_,
            physics::rotate_point_T(ray.direction,                   transform.rotation)
        };

        float lower = 0.0f, upper = ray.max_fraction;
        int32_t index = -1;

        for (int32_t i = 0; i < vertices_.size(); ++i)
        {
            float numerator   = utils::dot(vertices_.at(i) - rotated_ray.origin, normals_.at(i));
            float denominator = utils::dot(rotated_ray.direction,                normals_.at(i));

            if (denominator == 0.0f)
            {
                // Parallel to the edge and outside
                if (numerator < 0.0f)
                {
                    return false;
                }
            }
            else
            {
                // Note: we want this predicate without division:
                // lower < numerator / denominator, where denominator < 0
                // Since denominator < 0, we have to flip the inequality:
                // lower < numerator / denominator <==> denominator * lower > numerator.
                if (denominator < 0.0f && numerator < lower * denominator)
                {
                    // Increase lower.
                    // The segment enters this half-space.
                    lower = numerator / denominator;
                    index = i;
                }
                else if (denominator > 0.0f && numerator < upper * denominator)
                {
                    // Decrease upper.
                    // The segment exits this half-space.
                    upper = numerator / denominator;
                }
            }

            if (upper < lower)
            {
                return false;
            }
        }

        if (index >= 0)
        {

            output.fraction = lower;
            output.normal = physics::rotate_point(normals_.at(index), transform.rotation);

            return true;
        }

        return false;
    }

    PolygonShape PolygonShape::generate_polygon(const sf::Vector2u& window_size)
    {
        // Vertices
        int vert_start = 12, vert_end = 50;

        float half_width  = float(rand() % (vert_end - vert_start + 1) + vert_start);
        float half_heigth = float(rand() % (vert_end - vert_start + 1) + vert_start);

        std::vector<sf::Vector2f> vertices{
            { -half_width, -half_heigth },
            {  half_width, -half_heigth },
            {  half_width,  half_heigth },
            { -half_width,  half_heigth }
        };

        // Position
        sf::Vector2u pos_start = { 50, 50 }, pos_end = window_size - sf::Vector2u{ 50, 50 };

        sf::Vector2f position = {
            float(rand() % (pos_end.x - pos_start.x + 1) + pos_start.x),
            float(rand() % (pos_end.y - pos_start.y + 1) + pos_start.y)
        };

        // Creation
        return PolygonShape{ vertices, position };
    }

} // namespace physics
