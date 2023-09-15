#pragma once
#include "../../../Include/Utils/Functions.h"

#include "../../../Include/DataOperations/Shapes/RectangleShape.h"
#include "../../../Include/DataOperations/Shapes/CircleShape.h"


std::optional<sf::Vector2f> circles_collision(const CircleShape& circle_A, const CircleShape& circle_B);
std::optional<sf::Vector2f> rectangles_collision(const RectangleShape& rectangle_A, const RectangleShape& rectangle_B);
std::optional<sf::Vector2f> rectangle_circle_collision(const RectangleShape& rectangle, const CircleShape& circle);
