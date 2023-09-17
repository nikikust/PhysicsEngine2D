#pragma once
#include "../../Include/GUIEngine/Window.h"

#include "DataStorage.h"


class DataLoader
{
public:
    DataLoader(DataStorage& data_storage, graphics::Window& window);
    DataLoader() = delete;
    DataLoader(DataLoader&) = delete;
    DataLoader(DataLoader&&) = delete;
    ~DataLoader();

    int init();

private:
    
    void load_scene_1(); // specified entities
    void load_scene_2(); // random entities
    void load_scene_3(); // scene with ground
    void load_scene_4(); // stacking test

    // --- //
    DataStorage& data_storage_;

    graphics::Window& window_;
};
