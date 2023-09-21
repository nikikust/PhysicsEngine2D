#pragma once
#include <GameEngine/DataCore/DataStorage.h>
#include <GameEngine/PhysicsEngine/Shapes/CircleShape.h>
#include <GameEngine/PhysicsEngine/Shapes/PolygonShape.h>
#include <GameEngine/GUIEngine/Window.h>


namespace graphics
{
    class Painter
    {
    public:
        Painter(DataStorage& data_storage, graphics::Window& window);
        Painter() = delete;
        Painter(Painter&) = delete;
        Painter(Painter&&) = delete;
        ~Painter();

        // --- //

        void draw_polygon (std::shared_ptr<physics::PolygonShape> polygon);
        void draw_circle  (std::shared_ptr<physics::CircleShape>  circle );

    private:
        DataStorage& data_storage_;

        graphics::Window& window_;

        sf::CircleShape circle_brush;
        sf::ConvexShape polygon_brush;
    };
} // namespace graphics
