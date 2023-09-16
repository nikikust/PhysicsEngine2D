#pragma once
#include "../../Include/Modules/Window.h"

#include "DataStorage.h"


class DataLoader
{
public:
    DataLoader(DataStorage& data_storage, Window& window);
    DataLoader() = delete;
    DataLoader(DataLoader&) = delete;
    DataLoader(DataLoader&&) = delete;
    ~DataLoader();

    int init();

private:
    
    void load_scene_1();
    void load_scene_2();

    // --- //
    DataStorage& data_storage_;
    Window&      window_;
};
