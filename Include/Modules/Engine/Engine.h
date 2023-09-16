#pragma once
#include "../../../Include/DataOperations/DataStorage.h"
#include "../../../Include/Modules/Window.h"

#include "CollisionSolver.h"


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
