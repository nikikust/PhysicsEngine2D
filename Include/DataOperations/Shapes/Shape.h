#pragma once
#include "../../../Include/Utils/Functions.h"
#include "../../../Include/Modules/Engine/Material.h"


enum ShapeType
{
    Rectangle = 0,
    Circle    = 1
};


class Shape
{
public:
    Shape(ShapeType shape_type, const sf::Vector2f& position, float angle = 0, float mass = 1,
          const sf::Vector2f& linear_speed = { 0,0 }, float angular_speed = 0,
          const sf::Vector2f& linear_acceleration = { 0,0 }, const sf::Vector2f& angular_acceleration = { 0,0 }, const sf::Vector2f& force = { 0,0 },
          bool fixed_x = false, bool fixed_y = false, bool fixed_angle = false);

    virtual ~Shape() = default;

    sf::Vector2f get_center_of_mass   () const;
    float        get_moment_of_inertia() const;

    // --- Fields manipulations

    void set_position             (const sf::Vector2f& position);
    void set_angle                (float angle);
    void set_mass                 (float mass);
    void set_linear_speed         (const sf::Vector2f& linear_speed);
    void set_angular_speed        (float angular_speed);
    void set_linear_acceleration  (const sf::Vector2f& linear_acceleration);
    void set_angular_acceleration (const sf::Vector2f& angular_acceleration);
    void set_force                (const sf::Vector2f& force);
    void set_material_id          (int32_t material_id);

    sf::Vector2f get_position             () const;
    float        get_angle                () const;
    float        get_mass                 () const;
    sf::Vector2f get_linear_speed         () const;
    float        get_angular_speed        () const;
    sf::Vector2f get_linear_acceleration  () const;
    sf::Vector2f get_angular_acceleration () const;
    sf::Vector2f get_force                () const;
    int32_t      get_material_id          () const;

    ShapeType    get_shape () const;
    int32_t      get_id    () const;

    void move       (const sf::Vector2f& delta);
    void accelerate (const sf::Vector2f& delta);
    void rotate (float angle);
    void spin   (float angle);

protected:
    // --- Data
    sf::Vector2f position_;
    float        angle_;

    sf::Vector2f linear_speed_;
    float        angular_speed_;

    sf::Vector2f linear_acceleration_;
    sf::Vector2f angular_acceleration_;

    sf::Vector2f force_;

    float        mass_;

    // --- Calculated values
    float        moment_of_inertia_;

    // --- Flags
    bool         fixed_x_;
    bool         fixed_y_;
    bool         fixed_angle_;

    // --- Shape info
    ShapeType shape_type_;
    int32_t   id_;
    int32_t   material_id_;

    static int32_t max_object_id;
};
