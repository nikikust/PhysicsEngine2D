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
std::optional<CollisionInfo> polygon_circle_collision (std::shared_ptr<Shape> polygon_raw,   std::shared_ptr<Shape> circle_raw    );
std::optional<CollisionInfo> circle_polygon_collision (std::shared_ptr<Shape> circle_raw,    std::shared_ptr<Shape> polygon_raw   );

std::pair<float, float> polygon_projection(std::shared_ptr<PolygonShape> polygon, const sf::Vector2f& axis);
std::pair<float, float> circle_projection (std::shared_ptr<CircleShape>  circle,  const sf::Vector2f& axis);

sf::Vector2f circle_polygon_closest_point(std::shared_ptr<PolygonShape> polygon, std::shared_ptr<CircleShape> circle);

void resolve_collision(const CollisionInfo& collision, std::shared_ptr<Shape> shape_A, std::shared_ptr<Shape> shape_B);
