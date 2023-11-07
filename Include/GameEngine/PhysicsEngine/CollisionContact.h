#pragma once
#include <GameEngine/Utils/Functions.h>
#include <GameEngine/PhysicsEngine/Fixture.h>


namespace physics
{
    struct CollisionContact
    {
        Fixture* fixture_A;
        Fixture* fixture_B;

        sf::Vector2f contact_point;
        sf::Vector2f collision_normal;

        float depth;
        float elasticity;
    };
} // namespace physics
