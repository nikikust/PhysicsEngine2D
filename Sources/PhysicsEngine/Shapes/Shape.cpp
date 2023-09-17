#include "../../../Include/PhysicsEngine/Shapes/Shape.h"


int32_t Shape::max_object_id = 0;


Shape::Shape(ShapeType shape_type, const sf::Vector2f& position, float angle, float mass,
             const sf::Vector2f& linear_speed, float angular_speed,
             const sf::Vector2f& linear_acceleration, float angular_acceleration, const sf::Vector2f& force,
             bool fixed_x, bool fixed_y, bool fixed_angle)
    : position_(position), angle_(angle),
      linear_speed_(linear_speed), angular_speed_(angular_speed), 
      linear_acceleration_(linear_acceleration), angular_acceleration_(angular_acceleration), force_(force),
      mass_(mass), fixed_linear_({ fixed_x, fixed_y }), fixed_angle_(fixed_angle), shape_type_(shape_type)
{
    moment_of_inertia_ = 0;

    id_ = ++max_object_id;

    material_id_ = 1;
}


sf::Vector2f Shape::get_center_of_mass() const
{
    return position_;
}
float Shape::get_moment_of_inertia() const
{
    return moment_of_inertia_;
}

void Shape::set_position(const sf::Vector2f& position)
{
    position_ = position;
}
void Shape::set_angle(float angle)
{
    angle_ = angle;
}
void Shape::set_mass(float mass)
{
    mass_ = mass;
}
void Shape::set_linear_speed(const sf::Vector2f& linear_speed)
{
    linear_speed_ = linear_speed;
}
void Shape::set_angular_speed(float angular_speed)
{
    angular_speed_ = angular_speed;
}
void Shape::set_linear_acceleration(const sf::Vector2f& linear_acceleration)
{
    linear_acceleration_ = linear_acceleration;
}
void Shape::set_angular_acceleration(float angular_acceleration)
{
    angular_acceleration_ = angular_acceleration;
}
void Shape::set_force(const sf::Vector2f& force)
{
    force_ = force;
}

void Shape::set_material_id(int32_t material_id)
{
    material_id_ = material_id;
}

sf::Vector2f Shape::get_position() const
{
    return position_;
}
float Shape::get_angle() const
{
    return angle_;
}
float Shape::get_mass() const
{
    return mass_;
}
sf::Vector2f Shape::get_linear_speed() const
{
    return linear_speed_;
}
float Shape::get_angular_speed() const
{
    return angular_speed_;
}
sf::Vector2f Shape::get_linear_acceleration() const
{
    return linear_acceleration_;
}
float Shape::get_angular_acceleration() const
{
    return angular_acceleration_;
}
sf::Vector2f Shape::get_force() const
{
    return force_;
}
int32_t Shape::get_material_id() const
{
    return material_id_;
}

ShapeType Shape::get_shape() const
{
    return shape_type_;
}
int32_t Shape::get_id() const
{
    return id_;
}


void Shape::move(const sf::Vector2f& delta)
{
    position_ += delta;
}
void Shape::accelerate(const sf::Vector2f& delta)
{
    linear_speed_ += delta;
}
void Shape::rotate(float angle)
{
    angle_ += angle;
}
void Shape::spin(float angle)
{
    angular_speed_ += angle;
}

void Shape::update(float delta_time)
{
    linear_acceleration_ = force_ / mass_;

    linear_speed_  += linear_acceleration_  * delta_time;
    angular_speed_ += angular_acceleration_ * delta_time;

    if (fixed_linear_.first)
        linear_speed_.x = 0;
    if (fixed_linear_.second)
        linear_speed_.y = 0;
    if (fixed_angle_)
        angular_speed_ = 0;

    position_ += linear_speed_  * delta_time;
    angle_    += angular_speed_ * delta_time;

    force_ = { 0,0 };
}
void Shape::wrap_to_screen(const sf::Vector2u& window_size)
{
    sf::Vector2f pos{
        position_.x / (float)window_size.x,
        position_.y / (float)window_size.y
    };

    if (pos.x < 0)
        pos.x = 1.f - fmodf(fabsf(pos.x), 1.f);
    else if (pos.x > 1)
        pos.x = fmodf(pos.x, 1.f);

    if (pos.y < 0)
        pos.y = 1.f - fmodf(fabsf(pos.y), 1.f);
    else if (pos.y > 1)
        pos.y = fmodf(pos.y, 1.f);

    pos.x *= (float)window_size.x;
    pos.y *= (float)window_size.y;

    position_ = pos;
}

void Shape::set_linear_fixation(bool x, bool y)
{
    fixed_linear_ = { x, y };
}
void Shape::set_angular_fixation(bool a)
{
    fixed_angle_ = a;
}

std::pair<bool, bool> Shape::get_linear_fixation()
{
    return fixed_linear_;
}
bool Shape::get_angular_fixation()
{
    return fixed_angle_;
}
