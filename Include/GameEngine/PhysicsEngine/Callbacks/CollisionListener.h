#pragma once
#include <GameEngine/PhysicsEngine/CollisionContact.h>


namespace physics
{
    /// @brief You must NOT create or destroy bodies, fixtures, shapes and so on in these callbacks!
    class CollisionListener
    {
    public:
        virtual ~CollisionListener() = default;

        virtual void begin_contact(CollisionContact& contact) {};
        virtual void end_contact(CollisionContact& contact) {};
    };
} // namespace physics
