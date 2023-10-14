#pragma once
#include <GameEngine/Utils/Functions.h>
#include <GameEngine/Game/Entities/EntitiesStorage.h>


struct DataStorage
{
    DataStorage();
    DataStorage(DataStorage& ) = delete;
    DataStorage(DataStorage&&) = delete;

    ~DataStorage();

    // --- //

    sf::Vector2i screen_size;
    sf::Vector2f screen_size_halved;

    sf::Clock deltaClock;

    // --- Interface

    struct Menus 
    {
        bool CursorMessage = false;

        struct Fields
        {
            struct CursorMessage
            {
                std::string message = "";

                time_t elapse_at = time(0);
            } cursor_message;
        } fields;

        utils::PopUpState ConfirmExit;
    } menus;

    struct Settings 
    {
        bool autosave = false;
        int  autosave_interval_in_minutes = 3;

        bool disable_interface_on_screenshot = false;

        float background_color_3f[3] = { 0 };
        sf::Color background_color   = { 0, 0 ,0 ,255 };

    } settings;

    struct Status
    {
        time_t start_time_for_autosave = time(0);
        long long last_time = 0;
        float delta_time = 0.f;

        bool mouse_captured = false;
        bool keyboard_captured = false;

        enum class MovementMode
        {
            IDLE         = 0,
            MovingCamera = 1
        } movement_mode = MovementMode::IDLE;

        sf::Vector2f mouse_position_on_click  = { 0, 0 };
        sf::Vector2f camera_position_on_click = { 0, 0 };
        sf::Vector2f point_position_on_click  = { 0, 0 };

        bool make_screenshot = false;
        int  screenshot_frames_delay = 0;
    } status;

    struct Camera
    {
        sf::Vector2f position{ 0.f, 0.f };

        float scale_modifier = 1.0f;
    } camera;

    game::EntitiesStorage entities_storage;
};
