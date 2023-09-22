#pragma once
#include <GameEngine/Utils/Functions.h>


namespace graphics
{
    class Window;

    class Painter
    {
    public:
        Painter(graphics::Window& window);
        Painter() = delete;
        Painter(Painter&) = delete;
        Painter(Painter&&) = delete;
        ~Painter();

        // --- //

        void draw_polygon (const sf::Vector2f position, const std::vector<sf::Vector2f>& vertices, const sf::Color& color);
        void draw_circle  (const sf::Vector2f position, float radius,                              const sf::Color& color);

    private:
        graphics::Window& window_;

        sf::CircleShape circle_brush;
        sf::ConvexShape polygon_brush;
    };
} // namespace graphics
