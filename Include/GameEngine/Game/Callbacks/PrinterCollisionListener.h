#pragma once
#include <GameEngine/PhysicsEngine/Callbacks/CollisionListener.h>


namespace game
{
    class PrinterCollisionListener : public physics::CollisionListener
    {
        void begin_contact(physics::CollisionContact& contact);
        void end_contact(physics::CollisionContact& contact);
    };
} // namespace game
