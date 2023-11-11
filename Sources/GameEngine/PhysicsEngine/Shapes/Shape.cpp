#include <GameEngine/PhysicsEngine/Shapes/Shape.h>


namespace physics
{
    int32_t Shape::max_object_id = 0;


    Shape::Shape(ShapeType shape_type, const Vector& position)
        : position_(position), shape_type_(shape_type)
    {
        id_ = ++max_object_id;
    }
} // namespace physics
