#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include <imgui_stdlib.h>
#include <imgui_internal.h>

#include <SFML/Graphics.hpp>

#include <list>
#include <cmath>
#include <ctime>
#include <chrono>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <iostream>

#include <unordered_map>


#ifndef PI
#define PI 3.14159265
#endif
#define PI2 (3.14159265 / 2)
#define PI4 (3.14159265 / 4)

//#define DEBUG
//#define DEBUGTree
//#define DEBUGBodyTree
//#define DEBUGPrintTree
//#define USE_GRAVITY

namespace utils
{
    // --- Math

    struct PopUpState
    {
        bool is_open        = false;
        bool should_be_open = false;
    };

    int   minmax (int a, int num, int b);       // equal to: min(max(num, a), b);
    float minmax (float a, float num, float b);

    sf::Vector2f min(const sf::Vector2f& A, const sf::Vector2f& B);
    sf::Vector2f max(const sf::Vector2f& A, const sf::Vector2f& B);

    bool in(int a, int num, int b);       // true if: a <= num <= b

    int   randi(int   start, int   end);
    float randf(float start, float end, int amount);

    float length   (const sf::Vector2f& x);
    float distance (const sf::Vector2f& A, const sf::Vector2f& B);

    float length_squared   (const sf::Vector2f& x);
    float distance_squared (const sf::Vector2f& A, const sf::Vector2f& B);

    float dot   (const sf::Vector2f& A, const sf::Vector2f& B);
    float cross (const sf::Vector2f& A, const sf::Vector2f& B);

    sf::Vector2f normalize(const sf::Vector2f& vector);

    bool is_horizontal_move(const sf::Vector2i& A, const sf::Vector2i& B);
    bool is_horizontal_move(const sf::Vector2i& delta);

    sf::Vector2f rotate_point(const sf::Vector2f& point, float angle);


    bool file_exists(const std::string& path);
    std::string get_time_string();
    long long get_time_millisec();

    // --- ImGui

    inline namespace literals
    {
        char const* operator"" _C(const char8_t* str, std::size_t);
    }

    ImVec2 operator+ (const ImVec2& left, const ImVec2& right);
    ImVec2 operator- (const ImVec2& left, const ImVec2& right);
    bool   operator==(const ImVec2& left, const ImVec2& right);
    bool   operator!=(const ImVec2& left, const ImVec2& right);
    std::string operator*(std::string str, int mult);

    bool  block();                           // ImGUI::Sameline(); && return true;
    void  selectable_color(ImU32 color);
    float get_button_width(std::string text, ImGuiStyle& style);


    // --- SFML

    sf::Vector2f operator/(sf::Vector2i left, float right);

    enum class ButtonState
    {
        Up       = 0,
        Pressed  = 1,
        Down     = 2,
        Released = 3
    };

    extern bool ignore_input;
    extern ButtonState mouse_states [];
    extern ButtonState key_states   [];

    bool key_up       (const sf::Keyboard::Key& key);
    bool key_pressed  (const sf::Keyboard::Key& key);
    bool key_down     (const sf::Keyboard::Key& key);
    bool key_released (const sf::Keyboard::Key& key);

    bool mouse_up       (const sf::Mouse::Button& button);
    bool mouse_pressed  (const sf::Mouse::Button& button);
    bool mouse_down     (const sf::Mouse::Button& button);
    bool mouse_released (const sf::Mouse::Button& button);

} // namespace utils
