#pragma once
#include "../../Include/DataCore/DataStorage.h"
#include "../../Include/GUIEngine/Window.h"

#include "CollisionSolver.h"

namespace physics
{
    class Engine
    {
    public:
        Engine(DataStorage& data_storage, Window& window);
        Engine() = delete;
        Engine(Engine&) = delete;
        Engine(Engine&&) = delete;

        ~Engine();

        // --- //

        void update();

    private:
        DataStorage& data_storage_;
        Window&      window_;

        CollisionSolver collision_solver_;
    };
} // namespace physics
