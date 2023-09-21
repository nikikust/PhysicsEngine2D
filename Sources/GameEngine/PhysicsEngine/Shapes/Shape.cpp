#include <GameEngine/PhysicsEngine/Shapes/Shape.h>


namespace physics
{
    int32_t Shape::max_object_id = 0;


    Shape::Shape(ShapeType shape_type, const sf::Vector2f& position)
        : position_(position), shape_type_(shape_type)
    {
        id_ = ++max_object_id;
    }


    sf::Vector2f Shape::get_position() const
    {
        return position_;
    }

    void Shape::set_position(const sf::Vector2f& position)
    {
        position_ = position;
    }

    ShapeType Shape::get_shape() const
    {
        return shape_type_;
    }
    int32_t Shape::get_id() const
    {
        return id_;
    }
} // namespace physics
