#pragma once
#include <GameEngine/Utils/Functions.h>


namespace physics
{
    enum ShapeType
    {
        Rectangle = 0,
        Circle    = 1
    };

    class Shape
    {
    public:
        Shape(ShapeType shape_type, const sf::Vector2f& position);

        virtual ~Shape() = default;

        sf::Vector2f get_center_of_mass   () const;
        float        get_moment_of_inertia() const;

        // --- Fields manipulations

        sf::Vector2f get_position   () const;

        void         set_position   (const sf::Vector2f& position);

        ShapeType get_shape () const;
        int32_t   get_id    () const;

    protected:

        // --- Shape info
        ShapeType shape_type_;
        int32_t   id_;

        sf::Vector2f position_;

        // --- Config
        static int32_t      max_object_id;
    };
} // namespace physics
