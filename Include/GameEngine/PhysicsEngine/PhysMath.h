#pragma once
#include <GameEngine/Utils/Functions.h>
#include <GameEngine/PhysicsEngine/Ray.h>
#include <GameEngine/PhysicsEngine/Rotation.h>
#include <GameEngine/PhysicsEngine/ShapeAABB.h>


namespace physics
{
    struct Transform
    {
        sf::Vector2f position{};

        sf::Vector2f centroid{};
        Rotation     rotation{};

        Transform();
        Transform(Transform&);
        Transform(Transform&&) noexcept;
        Transform& operator=(const Transform& b);
    };
    bool operator== (const Transform& left, const Transform& right);
    bool operator!= (const Transform& left, const Transform& right);

    struct PhysicalData
    {
        float area     = 0.0f;
        float mass     = 0.0f;
        float inv_mass = 0.0f;

        sf::Vector2f centroid = { 0.0f, 0.0f };

        float mmoi     = 0.0f;
        float inv_mmoi = 0.0f;
    };

    /// @brief Rotates point around centroid, specified in transform
    /// @param point - point to rotate
    /// @param transform - rotation rule
    /// @return Rotated point
    sf::Vector2f rotate_point(const sf::Vector2f& point, const Transform& transform);

    /// @brief Rotates point around centroid, specified in transform
    /// @param point - point to rotate
    /// @param rotation - rotation rule
    /// @return Rotated point
    sf::Vector2f rotate_point(const sf::Vector2f& point, const Rotation& rotation);


    /// @brief Rotates point around centroid, specified in transform, and offsets it after
    /// @param point - point to rotate
    /// @param transform - rotation and offset rule
    /// @return Rotated and offsetted point
    sf::Vector2f rotate_and_move_point(const sf::Vector2f& point, const Transform& transform);


    /// @brief Rotates vertices by specified angle
    /// @param vertices - vertices to rotate
    /// @param angle - rotation angle
    /// @param offset - offset of polygon's center
    /// @return Rotated vertices
    std::vector<sf::Vector2f> rotate_polygon(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& offset, float angle);


    /// @brief Rotates vertices around centroid, specified in transform
    /// @param vertices - vertices to rotate
    /// @param transform - rotation and offset rule
    /// @param offset - offset of polygon's center
    /// @return Rotated vertices
    std::vector<sf::Vector2f> rotate_polygon(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& offset, const Transform& transform);


    /// @brief Calculates the area of the triangle
    /// @param A - Vector of the side A
    /// @param B - Vector of the side B
    /// @return Triangle's area
    float triangle_area(const sf::Vector2f& A, const sf::Vector2f& B);


    /// @brief Calculates the location of the triangle's centroid
    /// @param A - Vector of the side A
    /// @param B - Vector of the side B
    /// @return Triangle's centroid
    sf::Vector2f triangle_center(const sf::Vector2f& A, const sf::Vector2f& B);


    /// @brief Calculates the moment of inertia of the triangle
    /// @param A - Vector of the side A
    /// @param B - Vector of the side B 
    /// @param triangle_mass - Mass of the triangle
    /// @return 
    float triangle_mmoi(const sf::Vector2f& A, const sf::Vector2f& B, float triangle_mass);


    /// @brief Calculates the closest segment point to the specified point 
    /// @param point - Specified point
    /// @param A - End of the segment
    /// @param B - End of the segment
    /// @return Distance and point on the segment
    std::pair<float, sf::Vector2f> point_segment_distance_squared(const sf::Vector2f& point, const sf::Vector2f& A, const sf::Vector2f& B);


    /// @brief Returns true, if two floats are almost equal (to negate float inaccuracy effects)
    /// @param precision - precision area where floats are considered equal
    bool almost_equal(float A, float B, float precision = 0.01);


    /// @brief Returns true, if two vectors are almost equal (to negate float inaccuracy effects)
    /// @param precision - precision area where vectors are considered equal
    bool almost_equal(const sf::Vector2f& A, const sf::Vector2f& B, float precision = 0.01);


    // Inline section
    inline std::vector<sf::Vector2f> rotate_polygon(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& offset, float angle)
    {
        std::vector<sf::Vector2f> rotated_vertices = vertices;

        for (auto& vertex : rotated_vertices)
            vertex = utils::rotate_point(vertex + offset, angle);

        return rotated_vertices;
    }

    inline std::vector<sf::Vector2f> rotate_polygon(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& offset, const Transform& transform)
    {
        std::vector<sf::Vector2f> rotated_vertices = vertices;

        for (auto& vertex : rotated_vertices)
            vertex = physics::rotate_point(vertex + offset, transform);

        return rotated_vertices;
    }

    inline bool intersect(const Ray& ray, const sf::Vector2f& A, const sf::Vector2f& B, sf::Vector2f& result)
    {
        float a = B.y - A.y;
        float b = A.x - B.x;
        float c = -A.x * B.y + A.y * B.x;

        float t = (-a * ray.origin.x - b * ray.origin.y - c) / (a * ray.direction.x + b * ray.direction.y);

        if (t < 0)
            return false;

        // Координаты точки пересечения

        result.x = ray.origin.x + ray.direction.x * t;
        result.y = ray.origin.y + ray.direction.y * t;

        if ((utils::inf(A.x, result.x, B.x) || utils::inf(B.x, result.x, A.x)) && 
            (utils::inf(A.y, result.y, B.y) || utils::inf(B.y, result.y, A.y)))
            return true;

        return false;
    }

    inline bool intersect(const Ray& ray, const ShapeAABB& aabb, sf::Vector2f& result)
    {
        bool intersects = false;
        sf::Vector2f temp_result;

        sf::Vector2f aabb_top_right{ aabb.max.x, aabb.min.y };
        sf::Vector2f aabb_bottom_left{ aabb.min.x, aabb.max.y };

        // --- Top-Left - Top-Right

        intersects = intersect(ray, aabb.min, aabb_top_right, result);

        // --- Top-Right - Bottom-Right

        bool res = intersect(ray, aabb_top_right, aabb.max, temp_result);

        if (intersects && res)
            result = (utils::length_squared(temp_result - ray.origin) < utils::length_squared(result - ray.origin)) ? temp_result : result;
        else if (res)
        {
            intersects = true;
            result = temp_result;
        }

        // --- Bottom-Right - Bottom-Left

        res = intersect(ray, aabb.max, aabb_bottom_left, temp_result);

        if (intersects && res)
            result = (utils::length_squared(temp_result - ray.origin) < utils::length_squared(result - ray.origin)) ? temp_result : result;
        else if (res)
        {
            intersects = true;
            result = temp_result;
        }

        // --- Bottom-Left - Top-Left

        res = intersect(ray, aabb_bottom_left, aabb.min, temp_result);

        if (intersects && res)
            result = (utils::length_squared(temp_result - ray.origin) < utils::length_squared(result - ray.origin)) ? temp_result : result;
        else if (res)
        {
            intersects = true;
            result = temp_result;
        }

        // --- Result

        return intersects;
    }

    inline bool intersect(const Ray& ray, const ShapeAABB& aabb)
    {
        sf::Vector2f aabb_top_right{ aabb.max.x, aabb.min.y };
        sf::Vector2f aabb_bottom_left{ aabb.min.x, aabb.max.y };
        sf::Vector2f result_buf{};

        // --- Top-Left - Top-Right

        if (intersect(ray, aabb.min, aabb_top_right, result_buf))
            return true;

        // --- Top-Right - Bottom-Right

        if (intersect(ray, aabb_top_right, aabb.max, result_buf))
            return true;

        // --- Bottom-Right - Bottom-Left

        if (intersect(ray, aabb.max, aabb_bottom_left, result_buf))
            return true;

        // --- Bottom-Left - Top-Left

        if (intersect(ray, aabb_bottom_left, aabb.min, result_buf))
            return true;

        return false;
    }


    /// @brief Rotate point around centroid provided in transform
    inline sf::Vector2f rotate_point(const sf::Vector2f& point, const Transform& transform)
    {
        auto shifted_point = point - transform.centroid;

        return transform.centroid + sf::Vector2f{
            shifted_point.x * transform.rotation.get_cos() - shifted_point.y * transform.rotation.get_sin(),
            shifted_point.x * transform.rotation.get_sin() + shifted_point.y * transform.rotation.get_cos()
        };
    }


    /// @brief Inverse rotate point around centroid provided in transform
    inline sf::Vector2f rotate_point_T(const sf::Vector2f& point, const Transform& transform)
    {
        auto shifted_point = point - transform.centroid;

        return transform.centroid + sf::Vector2f{
             shifted_point.x * transform.rotation.get_cos() + shifted_point.y * transform.rotation.get_sin(),
            -shifted_point.x * transform.rotation.get_sin() + shifted_point.y * transform.rotation.get_cos()
        };
    }


    /// @brief Rotate point by matrix constructed from provided rotation
    inline sf::Vector2f rotate_point(const sf::Vector2f& point, const Rotation& rotation)
    {
        return sf::Vector2f{
            point.x * rotation.get_cos() - point.y * rotation.get_sin(),
            point.x * rotation.get_sin() + point.y * rotation.get_cos()
        };
    }


    /// @brief Inverse rotate point by matrix constructed from provided rotation
    inline sf::Vector2f rotate_point_T(const sf::Vector2f& point, const Rotation& rotation)
    {
        return sf::Vector2f{
             point.x * rotation.get_cos() + point.y * rotation.get_sin(),
            -point.x * rotation.get_sin() + point.y * rotation.get_cos()
        };
    }


    /// @brief Rotate point around centroid provided in transform and shift it
    inline sf::Vector2f rotate_and_move_point(const sf::Vector2f& point, const Transform& transform)
    {
        auto shifted_point = point - transform.centroid;

        return transform.position + transform.centroid + sf::Vector2f{
            shifted_point.x * transform.rotation.get_cos() - shifted_point.y * transform.rotation.get_sin(),
            shifted_point.x * transform.rotation.get_sin() + shifted_point.y * transform.rotation.get_cos()
        };
    }


    inline float triangle_area(const sf::Vector2f& A, const sf::Vector2f& B)
    {
        return utils::cross(A, B) / 2.f;
    }

    inline sf::Vector2f triangle_center(const sf::Vector2f& A, const sf::Vector2f& B)
    {
        return (A + B) / 3.f;
    }

    inline float triangle_mmoi(const sf::Vector2f& A, const sf::Vector2f& B, float triangle_mass)
    {
        return triangle_mass / 6.f * (utils::dot(A, A) + utils::dot(B, B) + utils::dot(A, B));
    }

    inline std::pair<float, sf::Vector2f> point_segment_distance_squared(const sf::Vector2f& p, const sf::Vector2f& A, const sf::Vector2f& B)
    {
        sf::Vector2f AB = B - A;
        sf::Vector2f Ap = p - A;

        float proj = utils::dot(Ap, AB);
        float AB_length_sqr = utils::length_squared(AB);
        float d = proj / AB_length_sqr;

        if (d <= 0.f)
            return { utils::distance_squared(p, A), A };
        else if (d >= 1.f)
            return { utils::distance_squared(p, B), B };
        else
            return { utils::distance_squared(p, A + AB * d), A + AB * d };
    }

    inline bool almost_equal(float A, float B, float precision)
    {
        return fabsf(B - A) < precision;
    }

    inline bool almost_equal(const sf::Vector2f& A, const sf::Vector2f& B, float precision)
    {
        return almost_equal(A.x, B.x) && almost_equal(A.y, B.y);
    }
} // namespace physics
