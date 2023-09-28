#pragma once
#include <GameEngine/Utils/Functions.h>
#include <GameEngine/PhysicsEngine/Rotation.h>


namespace physics
{
	struct Transform
	{
		sf::Vector2f position{};

		sf::Vector2f centroid{};
		Rotation     rotation{};
	};

	struct PhysicalData
	{
		float area     = 0.0f;
		float mass     = 0.0f;
		float inv_mass = 0.0f;

		sf::Vector2f centroid = { 0.0f, 0.0f };

		float mmoi = 0.0f;
	};

	/// @brief Rotates point around centroid, specified in transform
	/// @param point - point to rotate
	/// @param transform - rotation rule
	/// @return Rotated point
	sf::Vector2f rotate_point(const sf::Vector2f& point, const Transform& transform);


	/// @brief Rotates point around centroid, specified in transform, and offsets it after
	/// @param point - point to rotate
	/// @param transform - rotation and offset rule
	/// @return Rotated and offsetted point
	sf::Vector2f rotate_and_move_point(const sf::Vector2f& point, const Transform& transform);


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
} // namespace physics
