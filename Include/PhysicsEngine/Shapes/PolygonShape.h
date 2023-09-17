#pragma once
#include "Shape.h"


class PolygonShape : public Shape
{
public:
    PolygonShape(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& position, float angle = 0, float mass = 1,
                 const sf::Vector2f& linear_speed = { 0,0 }, float angular_speed = 0,
                 const sf::Vector2f& linear_acceleration = { 0,0 }, float angular_acceleration = 0,
                 const sf::Vector2f& force = { 0,0 },
                 bool fixed_x = false, bool fixed_y = false, bool fixed_angle = false);

    void set_vertices(const std::vector<sf::Vector2f>& vertices);

    const std::vector<sf::Vector2f>& get_vertices() const;

    static PolygonShape generate_rectangle(const sf::Vector2u& window_size);

private:
    void update_moment_of_inertia();


    std::vector<sf::Vector2f> vertices_;
};
