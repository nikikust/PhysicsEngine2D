#pragma once
#include "../../../Include/Utils/Functions.h"

#include "../../../Include/DataOperations/Shapes/PolygonShape.h"
#include "../../../Include/DataOperations/Shapes/CircleShape.h"


struct CollisionInfo
{
	sf::Vector2f collision_point;
	sf::Vector2f collision_normal;

	float depth;
};

std::optional<CollisionInfo> circles_collision        (std::shared_ptr<Shape> circle_A_raw,  std::shared_ptr<Shape> circle_B_raw  );
std::optional<CollisionInfo> polygons_collision       (std::shared_ptr<Shape> polygon_A_raw, std::shared_ptr<Shape> polygon_B_raw );
std::optional<CollisionInfo> polygon_circle_collision (std::shared_ptr<Shape> rectangle_raw, std::shared_ptr<Shape> circle_raw    );
std::optional<CollisionInfo> circle_polygon_collision (std::shared_ptr<Shape> circle_raw,    std::shared_ptr<Shape> rectangle_raw );

std::pair<float, float> min_max_projection(std::shared_ptr<PolygonShape> polygon, const sf::Vector2f& axis);
