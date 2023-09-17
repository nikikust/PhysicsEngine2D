#pragma once
#include "../../Include/DataOperations/DataStorage.h"


class Window
{
public:
    Window(DataStorage& data_storage, const std::string window_title);
    Window() = delete;
    Window(Window&) = delete;
    Window(Window&&) = delete;

    ~Window(); 
    
    // --- //
    
    void close();

    void on_resize(sf::Event& event);
    bool poll_event(sf::Event& event);

    bool has_focus();
    bool is_open();

    sf::Vector2i get_cursor_position();

    void set_cursor_position(sf::Vector2i position);
    void hide_mouse();
    void show_mouse();

    void update();
    void cls();
    void flip();

    sf::RenderWindow& get_render_area();

private:
    DataStorage& data_storage_;

    sf::RenderWindow window_;

    ImGuiIO* imgui_io_;

};