#include <GameEngine/PhysicsEngine/Shapes/CircleShape.h>


namespace physics
{
    CircleShape::CircleShape(float radius, const Vector& position)
        : Shape(ShapeType::Circle, position), radius_(radius)
    {
    }

    // --- //

    PhysicalData CircleShape::calculate_physical_data(float density) const
    {
        float area = PIf * radius_ * radius_;
        float mass = area * density;
        float mmoi = PI4f * powf(radius_, 4);

        return { area , mass, (mass > 0.f) ? 1.f / mass : 0.f, {}, mmoi };
    }

    bool CircleShape::cast_ray(const Ray& ray, const Transform& transform, RayHitInfo& output) const
    {
        auto global_position = physics::rotate_and_move_point(position_, transform);

        Vector s = ray.origin - global_position;
        float C = physics::dot(s, s) - radius_ * radius_;

        // Solve quadratic equation.
        float B = physics::dot(s, ray.direction); // = b/2
        float A = physics::dot(ray.direction, ray.direction);
        float discr = B * B - A * C; // D/4

        // Check for negative discriminant and short segment.
        if (discr < 0.0f || physics::almost_equal(A, 0.f))
        {
            return false;
        }

        // Find the point of intersection of the line with the circle.
        float t = -(B + sqrtf(discr));

        if (t >= 0.f)
        {
            t /= A;

            output.fraction = t;
            output.normal = physics::normalize(s + t * ray.direction);
            return true;
        }

        return false;
    }


    CircleShape CircleShape::generate_circle(const Vector& window_size)
    {
        // Radius
        int rad_start = 25, rad_end = 100;

        float radius = float(rand() % (rad_end - rad_start + 1) + rad_start);

        // Position
        Vector pos_start = { 100, 100 }, pos_end = window_size - Vector{ 100, 100 };

        Vector position = {
            float(rand() % int((pos_end.x - pos_start.x + 1) + pos_start.x)),
            float(rand() % int((pos_end.y - pos_start.y + 1) + pos_start.y))
        };

        // Creation
        return CircleShape{ radius, position };
    }

} // namespace physics