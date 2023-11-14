#pragma once
#include <GameEngine/PhysicsEngine/Rotation.h>

#include <vector>
#include <algorithm>
#include <unordered_map>


#ifndef PI
#define PI 3.14159265
#endif
#define PI2 (3.14159265 / 2)
#define PI4 (3.14159265 / 4)

#define PIf float(PI)
#define PI2f float(PI / 2)
#define PI4f float(PI / 4)


namespace physics
{
    class ShapeAABB;

    struct Vector
    {
        Vector() : x(0.f), y(0.f) {}
        Vector(float x, float y) : x(x), y(y) {}

        float x, y;
    };

    struct Transform
    {
        Vector position{};

        Vector centroid{};
        Rotation rotation{};

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

        Vector centroid = { 0.0f, 0.0f };

        float mmoi     = 0.0f;
        float inv_mmoi = 0.0f;
    };

    /// @brief Rotates point around centroid, specified in transform
    /// @param point - point to rotate
    /// @param transform - rotation rule
    /// @return Rotated point
    Vector rotate_point(const Vector& point, const Transform& transform);

    /// @brief Rotates point around centroid, specified in transform
    /// @param point - point to rotate
    /// @param rotation - rotation rule
    /// @return Rotated point
    Vector rotate_point(const Vector& point, const Rotation& rotation);


    /// @brief Rotates point around centroid, specified in transform, and offsets it after
    /// @param point - point to rotate
    /// @param transform - rotation and offset rule
    /// @return Rotated and offsetted point
    Vector rotate_and_move_point(const Vector& point, const Transform& transform);


    /// @brief Rotates vertices by specified angle
    /// @param vertices - vertices to rotate
    /// @param angle - rotation angle
    /// @param offset - offset of polygon's center
    /// @return Rotated vertices
    std::vector<Vector> rotate_polygon(const std::vector<Vector>& vertices, const Vector& offset, float angle);


    /// @brief Rotates vertices around centroid, specified in transform
    /// @param vertices - vertices to rotate
    /// @param transform - rotation and offset rule
    /// @param offset - offset of polygon's center
    /// @return Rotated vertices
    std::vector<Vector> rotate_polygon(const std::vector<Vector>& vertices, const Vector& offset, const Transform& transform);


    /// @brief Calculates the area of the triangle
    /// @param A - Vector of the side A
    /// @param B - Vector of the side B
    /// @return Triangle's area
    float triangle_area(const Vector& A, const Vector& B);


    /// @brief Calculates the location of the triangle's centroid
    /// @param A - Vector of the side A
    /// @param B - Vector of the side B
    /// @return Triangle's centroid
    Vector triangle_center(const Vector& A, const Vector& B);


    /// @brief Calculates the moment of inertia of the triangle
    /// @param A - Vector of the side A
    /// @param B - Vector of the side B 
    /// @param triangle_mass - Mass of the triangle
    /// @return 
    float triangle_mmoi(const Vector& A, const Vector& B, float triangle_mass);


    /// @brief Calculates the closest segment point to the specified point 
    /// @param point - Specified point
    /// @param A - End of the segment
    /// @param B - End of the segment
    /// @return Distance and point on the segment
    std::pair<float, Vector> point_segment_distance_squared(const Vector& point, const Vector& A, const Vector& B);


    /// @brief Returns true, if two floats are almost equal (to negate float inaccuracy effects)
    /// @param precision - precision area where floats are considered equal
    bool almost_equal(float A, float B, float precision = 0.01);


    /// @brief Returns true, if two vectors are almost equal (to negate float inaccuracy effects)
    /// @param precision - precision area where vectors are considered equal
    bool almost_equal(const Vector& A, const Vector& B, float precision = 0.01);
} // namespace physics

#include "PhysMath.inl"

