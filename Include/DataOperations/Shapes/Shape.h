#pragma once
#include "../../../Include/Utils/Functions.h"


enum ShapeType
{
    Rectangle = 0,
    Circle    = 1
};

class Shape
{
protected:

public:
    Shape(ShapeType shape_type, const sf::Vector2f& position, float angle = 0,
          const sf::Vector2f& linear_speed = { 0,0 }, float angular_speed = 0,
          float mass = 1, bool fixed_x = false, bool fixed_y = false, bool fixed_angle = false);

    virtual ~Shape() = default;

    sf::Vector2f get_center_of_mass   () const;
    float        get_moment_of_inertia() const;

    // --- Fields manipulations

    void set_position      (const sf::Vector2f& position);
    void set_angle         (float angle);
    void set_linear_speed  (const sf::Vector2f& linear_speed);
    void set_angular_speed (float angular_speed);
    void set_mass          (float mass);

    sf::Vector2f get_position      () const;
    float        get_angle         () const;
    sf::Vector2f get_linear_speed  () const;
    float        get_angular_speed () const;
    float        get_mass          () const;
    ShapeType    get_shape         () const;

    void move   (const sf::Vector2f& delta);
    void rotate (float angle);

protected:
    // --- Data
    sf::Vector2f position_;
    float        angle_;

    sf::Vector2f linear_speed_;
    float        angular_speed_;

    float        mass_;

    // --- Calculated values
    float        moment_of_inertia_;

    // --- Flags
    bool         fixed_x_;
    bool         fixed_y_;
    bool         fixed_angle_;

    // --- Shape
    ShapeType shape_type_;
};
