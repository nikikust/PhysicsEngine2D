#pragma once
#include <GameEngine/Utils/Functions.h>


struct DataStorage;

namespace graphics
{
    class Window;

    struct DebugDraw
    {
        enum { Circle, Polygon, Border } type;

        sf::Vector2f position;
        sf::Color    color;

        // Circle part
        float radius;
        float angle;

        // Polygon part
        std::vector<sf::Vector2f> vertices;
        float outline_thickness;
    };

    class Painter
    {
    public:
        Painter(graphics::Window& window, DataStorage& data_storage);
        Painter() = delete;
        Painter(Painter&) = delete;
        Painter(Painter&&) = delete;
        ~Painter();

        // --- //

        void draw_polygon (const sf::Vector2f& position, const std::vector<sf::Vector2f>& vertices, const sf::Color& color);
        void draw_circle  (const sf::Vector2f& position, float radius, float angle,                 const sf::Color& color, bool draw_rotation_line = true);

        void draw_border  (const sf::Vector2f& position, const std::vector<sf::Vector2f>& vertices, const sf::Color& color, float outline_thickness);

#ifdef DEBUG
        void draw_debug(const std::vector<DebugDraw>& debug_entities);
#endif // DEBUG

    private:
        graphics::Window& window_;
        DataStorage& data_storage_;


        sf::CircleShape    circle_brush;
        sf::RectangleShape circle_angle_brush;

        sf::ConvexShape polygon_brush;
    };
} // namespace graphics
