#pragma once
#include <GameEngine/GUIEngine/Window.h>
#include <GameEngine/DataCore/DataStorage.h>
#include <GameEngine/PhysicsEngine/Engine.h>

#include <GameEngine/Game/Entities/CircleEntity.h>
#include <GameEngine/Game/Entities/PolygonEntity.h>
#include <GameEngine/Game/Entities/ComplexEntity.h>


class DataLoader
{
public:
    DataLoader(DataStorage& data_storage, graphics::Window& window, physics::Engine& engine);
    DataLoader() = delete;
    DataLoader(DataLoader&) = delete;
    DataLoader(DataLoader&&) = delete;
    ~DataLoader();

    int init();

private:

    // --- //
    DataStorage& data_storage_;

    graphics::Window& window_;

    physics::Engine& engine_;
};
