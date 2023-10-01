#include <GameEngine/Utils/Functions.h>


namespace utils
{
    // --- Math
    int   minmax(int a, int num, int b) 
    { 
        return (a > num) ? a : (b < num) ? b : num; 
    }
    float minmax(float a, float num, float b) 
    { 
        return (a > num) ? a : (b < num) ? b : num; 
    }

    sf::Vector2f min(const sf::Vector2f& A, const sf::Vector2f& B)
    {
        return { fminf(A.x, B.x), fminf(A.y, B.y) };
    }
    sf::Vector2f max(const sf::Vector2f& A, const sf::Vector2f& B)
    {
        return { fmaxf(A.x, B.x), fmaxf(A.y, B.y) };
    }

    bool in(int a, int num, int b)
    {
        return (num >= a && num <= b);
    }

    int randi(int start, int end)
    {
        return start + rand() % (end - start + 1);
    }
    float randf(float start, float end, int amount)
    {
        return start + (rand() % amount) / float(amount) * (end - start);
    }

    float length(const sf::Vector2f& x)
    {
        return sqrt(x.x * x.x + x.y * x.y);
    }
    float distance(const sf::Vector2f& A, const sf::Vector2f& B)
    {
        sf::Vector2f diff = B - A;

        return sqrt(diff.x * diff.x + diff.y * diff.y);
    }

    float length_squared(const sf::Vector2f& x)
    {
        return x.x * x.x + x.y * x.y;
    }
    float distance_squared(const sf::Vector2f& A, const sf::Vector2f& B)
    {
        sf::Vector2f diff = B - A;

        return diff.x * diff.x + diff.y * diff.y;
    }

    float dot(const sf::Vector2f& A, const sf::Vector2f& B)
    {
        return A.x * B.x + A.y * B.y;
    }
    float cross(const sf::Vector2f& A, const sf::Vector2f& B)
    {
        return A.x * B.y - B.x * A.y;
    }

    sf::Vector2f normalize(const sf::Vector2f& vector)
    {
        return vector / utils::length(vector);
    }

    bool is_horizontal_move(const sf::Vector2i& A, const sf::Vector2i& B)
    {
        return (abs(B.x - A.x) >= abs(B.y - A.y));
    }
    bool is_horizontal_move(const sf::Vector2i& delta)
    {
        return (abs(delta.x) >= abs(delta.y));
    }

    sf::Vector2f rotate_point(const sf::Vector2f& point, float angle)
    {
        return {
            point.x * cosf(angle) - point.y * sinf(angle),
            point.x * sinf(angle) + point.y * cosf(angle)
        };
    }

    bool file_exists(const std::string& path)
    {
        try
        {
            std::ifstream test(path);
            if (test.is_open())
            {
                test.close();
                return true;
            }
        }
        catch (const std::exception& err)
        {
            std::cout << "file_exists(): " << err.what() << std::endl;
        }

        return false;
    }
    std::string get_time_string()
    {
        // --- //

        std::ostringstream oss;

#ifdef WIN32
        tm local_time;
        time_t time = std::time(nullptr);

        localtime_s(&local_time, &time);

        oss << std::put_time(&local_time, "%d-%m-%Y_%H-%M-%S");
#else
        struct tm* local_time;
        time_t t = time(NULL);

        local_time = localtime(&t);

        oss << std::put_time(local_time, "%d-%m-%Y_%H-%M-%S");
#endif

        return oss.str();
    }
    long long get_time_millisec()
    {
        auto time = std::chrono::system_clock::now();
        auto since_epoch = time.time_since_epoch();

        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);

        return millis.count();
    }

    // --- ImGui

    inline namespace literals
    {
        char const* operator"" _C(const char8_t* str, std::size_t)
        {
            return reinterpret_cast<const char*>(str);
        }
    }

    ImVec2 operator+(const ImVec2& left, const ImVec2& right)
    {
        return ImVec2(left.x + right.x, left.y + right.y);
    }
    ImVec2 operator-(const ImVec2& left, const ImVec2& right)
    {
        return ImVec2(left.x - right.x, left.y - right.y);
    }
    bool operator==(const ImVec2& left, const ImVec2& right)
    {
        return left.x == right.x && left.y == right.y;
    }
    bool operator!=(const ImVec2& left, const ImVec2& right)
    {
        return left.x != right.x || left.y != right.y;
    }
    std::string operator*(std::string str, int mult)
    {
        std::string buf = "";
        while (mult--)
            buf += str;
        return buf;
    }

    bool block()
    {
        ImGui::SameLine();
        return true;
    }
    void selectable_color(ImU32 color)
    {
        ImVec2 p_min = ImGui::GetItemRectMin();
        ImVec2 p_max = ImGui::GetItemRectMax();
        ImGui::GetWindowDrawList()->AddRectFilled(p_min, p_max, color);
    }
    float get_button_width(std::string text, ImGuiStyle& style)
    {
        return ImGui::CalcTextSize(text.c_str()).x + style.FramePadding.x * 2 + style.ItemSpacing.x;
    }

    // --- SFML

    sf::Vector2f operator/(sf::Vector2i left, float right)
    {
        return sf::Vector2f((float)left.x / right, (float)left.y / right);
    }

    bool ignore_input = false;
    ButtonState mouse_states [sf::Mouse::ButtonCount] = { ButtonState::Up };
    ButtonState key_states   [sf::Keyboard::KeyCount] = { ButtonState::Up };

    bool key_up       (const sf::Keyboard::Key& key)
    {
        if (ignore_input)
            return false;
        return !sf::Keyboard::isKeyPressed(key);
    }
    bool key_pressed  (const sf::Keyboard::Key& key)
    {
        if (key_states[key] == ButtonState::Pressed) {
            key_states[key]  = ButtonState::Down;
            if (!ignore_input)
                return true;
        }
        return false;
    }
    bool key_down     (const sf::Keyboard::Key& key)
    {
        if (ignore_input)
            return false;
        return sf::Keyboard::isKeyPressed(key);
    }
    bool key_released (const sf::Keyboard::Key& key)
    {
        if (key_states[key] == ButtonState::Released) {
            key_states[key]  = ButtonState::Up;
            if (!ignore_input)
                return true;
        }
        return false;
    }

    bool mouse_up       (const sf::Mouse::Button& button)
    {
        if (ignore_input)
            return false;
        return !sf::Mouse::isButtonPressed(button);
    }
    bool mouse_pressed  (const sf::Mouse::Button& button)
    {
        if (mouse_states[button] == ButtonState::Pressed) {
            mouse_states[button]  = ButtonState::Down;
            if (!ignore_input)
                return true;
        }
        return false;
    }
    bool mouse_down     (const sf::Mouse::Button& button)
    {
        if (ignore_input)
            return false;
        return sf::Mouse::isButtonPressed(button);
    }
    bool mouse_released (const sf::Mouse::Button& button)
    {
        if (mouse_states[button] == ButtonState::Released) {
            mouse_states[button]  = ButtonState::Up;
            if (!ignore_input)
                return true;
        }
        return false;
    }
} // namespace utils
