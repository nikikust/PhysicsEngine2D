#pragma once
#include <GameEngine/GUIEngine/Window.h>
#include <GameEngine/DataCore/DataStorage.h>
#include <GameEngine/PhysicsEngine/Engine.h>


class DataEditor
{
public:
    DataEditor(DataStorage& data_storage, graphics::Window& window, physics::Engine& engine);
    DataEditor() = delete;
    DataEditor(DataEditor&) = delete;
    DataEditor(DataEditor&&) = delete;
    ~DataEditor();

    // --- //

    void save_mouse_position_on_click();
    bool mouse_kept_position();

    void save_camera_position();
    void restore_camera_position();
    void start_moving_camera();
    void stop_moving_camera();
    void move_camera(sf::Vector2i delta);

    bool mouse_io_is_released();
    bool keyboard_io_is_released();

    bool is_idle_mode();
    bool is_camera_moving_mode();

    void create_message(const std::string& message, int timeout = 5);
    bool message_is_opened();
    void close_message();

    void zoom_out();
    void zoom_in();

    void screenshot_with_interface();
    void screenshot_without_interface();
    void check_screenshot_status();

    void flip_exit_popup_state();

    void load_scene(int32_t id);

private:
    void make_screenshot();

    void load_scene_1(); // specified entities
    void load_scene_2(); // scene with ships
    void load_scene_3(); // random entities with ground
    void load_scene_4(); // bullets test

private:
    DataStorage& data_storage_;

    graphics::Window& window_;
    physics::Engine&  engine_;
};
