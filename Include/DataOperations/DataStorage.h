#pragma once
#include "../../Include/Utils/Functions.h"
#include "../../Include/DataOperations/Shapes/Shape.h"

#include <thread>


#define SPRITES_AMOUNT_HORIZONTAL 10
#define SPRITES_AMOUNT_VERTICAL   10


struct DataStorage
{
    DataStorage();
    DataStorage(DataStorage&) = delete;
    DataStorage(DataStorage&&) = delete;

    ~DataStorage();

    // --- //

    sf::Vector2i screen_size;

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

        bool mouse_captured    = false;
        bool keyboard_captured = false;

        enum class MovementMode
        {
            IDLE              = 0,
            MovingCamera      = 1
        } movement_mode = MovementMode::IDLE;

        sf::Vector2i mouse_position_on_click  = { 0, 0 };
        sf::Vector2i camera_position_on_click = { 0, 0 };
        sf::Vector2i point_position_on_click  = { 0, 0 };

        bool make_screenshot         = false;
        int  screenshot_frames_delay = 0;
    } status;

    struct Camera
    {
        sf::Vector2i position{ 0, 0 };

        float scale_modifier = 0.0;
        float scale_modifier_as_pow2 = 1;
    } camera;


    // --- Renderer

    struct SceneObjects
    {
        std::vector<std::shared_ptr<Shape>> shapes{};
    } scene_objects;

};
