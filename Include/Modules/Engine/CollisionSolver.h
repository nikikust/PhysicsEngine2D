#pragma once
#include "../../../Include/Utils/Functions.h"

#include "../../../Include/DataOperations/Shapes/RectangleShape.h"
#include "../../../Include/DataOperations/Shapes/CircleShape.h"


struct CollisionInfo
{
	sf::Vector2f collision_point;
	sf::Vector2f collision_normal;

	float depth;
};

std::optional<CollisionInfo> circles_collision          (std::shared_ptr<Shape> circle_A_raw,    std::shared_ptr<Shape> circle_B_raw);
std::optional<CollisionInfo> rectangles_collision       (std::shared_ptr<Shape> rectangle_A_raw, std::shared_ptr<Shape> rectangle_B_raw);
std::optional<CollisionInfo> rectangle_circle_collision (std::shared_ptr<Shape> rectangle_raw,   std::shared_ptr<Shape> circle_raw);
