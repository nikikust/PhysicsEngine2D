#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include <imgui_stdlib.h>
#include <imgui_internal.h>

#include <SFML/Graphics.hpp>

#include <GameEngine/PhysicsEngine/PhysMath.h>

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

#define PIf float(PI)
#define PI2f float(PI / 2)
#define PI4f float(PI / 4)


//#define DAMPING

//#define DEBUG
//#define DEBUGTree       // requires DEBUG
//#define DEBUGBodyTree   // requires DEBUGTree
//#define DEBUGPrintTree  // requires DEBUGTree

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

    bool in(int a, int num, int b);       // true if: a <= num <= b
    bool inf(float a, float num, float b);

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


    // Inline section
    inline sf::Vector2f convert_to_sf(const physics::Vector& right)
    {
        return sf::Vector2f(right.x, right.y);
    }
    inline physics::Vector convert_to_phys(const sf::Vector2f& right)
    {
        return physics::Vector(right.x, right.y);
    }

    inline std::vector<sf::Vector2f> convert_to_sf(const std::vector<physics::Vector>& right)
    {
        std::vector<sf::Vector2f> vec;
        vec.reserve(right.size());

        for (const auto& vertex : right)
            vec.push_back(utils::convert_to_sf(vertex));

        return vec;
    }

    inline sf::Vector2f min(const sf::Vector2f& A, const sf::Vector2f& B)
    {
        return { fminf(A.x, B.x), fminf(A.y, B.y) };
    }
    inline sf::Vector2f max(const sf::Vector2f& A, const sf::Vector2f& B)
    {
        return { fmaxf(A.x, B.x), fmaxf(A.y, B.y) };
    }

    inline sf::Vector2f abs(const sf::Vector2f& X)
    {
        return sf::Vector2f(fabsf(X.x), fabsf(X.y));
    }

    template<typename T>
    inline void swap(T& a, T& b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }

    inline float length(const sf::Vector2f& x)
    {
        return sqrt(x.x * x.x + x.y * x.y);
    }
    inline float distance(const sf::Vector2f& A, const sf::Vector2f& B)
    {
        sf::Vector2f diff = B - A;

        return sqrt(diff.x * diff.x + diff.y * diff.y);
    }

    inline float length_squared(const sf::Vector2f& x)
    {
        return x.x * x.x + x.y * x.y;
    }
    inline float distance_squared(const sf::Vector2f& A, const sf::Vector2f& B)
    {
        sf::Vector2f diff = B - A;

        return diff.x * diff.x + diff.y * diff.y;
    }

    inline sf::Vector2f normalize(const sf::Vector2f& vector)
    {
        auto length = utils::length(vector);

        if (length == 0.f)
            return { 1.f, 0.f };

        return vector / length;
    }

    inline float dot(const sf::Vector2f& A, const sf::Vector2f& B)
    {
        return A.x * B.x + A.y * B.y;
    }
    inline float cross(const sf::Vector2f& A, const sf::Vector2f& B)
    {
        return A.x * B.y - B.x * A.y;
    }

    inline sf::Vector2f rotate_point(const sf::Vector2f& point, float angle)
    {
        return {
            point.x * cosf(angle) - point.y * sinf(angle),
            point.x * sinf(angle) + point.y * cosf(angle)
        };
    }
} // namespace utils
