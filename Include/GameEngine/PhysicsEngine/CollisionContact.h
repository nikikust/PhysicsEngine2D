#pragma once
#include <GameEngine/PhysicsEngine/PhysMath.h>
#include <GameEngine/PhysicsEngine/Fixture.h>


namespace physics
{
    struct CollisionContact
    {
        Fixture* fixture_A;
        Fixture* fixture_B;

        Vector contact_point;
        Vector collision_normal;

        float depth;
        float elasticity;
    };
} // namespace physics
